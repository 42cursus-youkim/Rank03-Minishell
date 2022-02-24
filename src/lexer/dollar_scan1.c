#include "minishell.h"

static t_res	expansion_last_check(t_expansion_scan_info *info, int *i)
{
	if (is_brace_open(*info->buf))
	{
		del_ast_expansions(info->expansions);
		free(*info->buf);
		return (error_msg_return(
				(char *[]){
					BRED, MINISHELL, BRACE_ERROR, MULTILINE_ERROR, NULL}));
	}
	if (info->end < info->begin)
		if (expansions_update_with_brace(info, *i - 1, false) == ERR)
			return (ERR);
	return (OK);
}

static t_res	brace_closed_n_other_check(t_expansion_scan_info *info, int *i)
{
	if (info->str[*i] == '}' && info->end < info->begin)
		if (expansions_update_with_brace(info, *i, true) == ERR)
			return (ERR);
	if (ft_str_append(info->buf, info->str[*i]) == ERR)
		return (free_n_return(info->buf, error_malloc_msg()));
	return (OK);
}

static t_res	expansion_scan_loop(t_expansion_scan_info *info, int *i)
{
	t_res	res;

	while (is_scan_continuos(*info->buf, info->str[++*i]))
	{
		if (!is_brace_open(*info->buf)
			&& !is_variable_char_valid(info->str[*i]))
		{
			if (info->end < info->begin)
				if (expansions_update_with_brace(info, *i - 1, false) == ERR)
					return (ERR);
			if (is_multi_expansions(*info, *i))
			{
				res = expansion_location_init(info, i);
				if (res == OK)
					continue ;
				if (res == ERR)
					return (ERR);
			}
		}
		if (brace_closed_n_other_check(info, i) == ERR)
			return (ERR);
	}
	return (expansion_last_check(info, i));
}

static t_res	expansion_scan(t_list **list, char **buf, char *str, int *idx)
{
	t_expansion_scan_info	info;
	int						i;
	t_list					*list_element;

	info.buf = buf;
	info.str = str;
	info.idx = idx;
	info.start_i = ft_strlen(*buf);
	i = *info.idx;
	if (!is_1stchar_valid(str[i + 1]))
		return (UNSET);
	info.expansions = new_ast_expansions((t_AST_expansion *[]){NULL});
	if (!info.expansions)
		return (free_n_return(buf, error_malloc_msg()));
	if (expansion_location_init(&info, &i) == ERR)
		return (ERR);
	if (expansion_scan_loop(&info, &i) == ERR)
		return (ERR);
	if (list_element_create(&list_element, *info.buf, info.expansions) == ERR)
		return (free_n_return(buf, ERR));
	ft_list_append(list, list_element);
	*idx = --i;
	return (OK);
}

t_res	dollar_scan(t_list **list, char **buf, char *str, int *idx)
{
	int		i;
	char	last_quote;
	t_res	res;

	i = *idx;
	if (str[i] == '$')
	{
		if (is_quotes_open(&last_quote, *buf) && last_quote == '\'')
			return (UNSET);
		res = expansion_scan(list, buf, str, &i);
		if (res == UNSET)
			return (UNSET);
		if (res == ERR)
			return (ERR);
		*idx = i;
		free(*buf);
		*buf = new_str("");
		if (!buf)
			return (error_malloc_msg());
		return (OK);
	}
	return (UNSET);
}
