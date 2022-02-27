#include "minishell.h"

static t_res	expansion_last_check(t_expansion_scan_info *info, int *i)
{
	if (is_brace_open(info->data->buf))
	{
		del_ast_expansions(info->expansions);
		free(info->data->buf);
		info->data->env_flag = true;
		return (error_with_exitcode((char *[]){
				BRED, MINISHELL, BRACE_ERROR, MULTILINE_ERROR, NULL},
			info->data->env, 2));
	}
	if (info->end < info->begin)
		if (expansions_update_with_brace(info, *i - 1, false) == ERR)
			return (ERR);
	return (OK);
}

static t_res	brace_closed_n_other_check(t_expansion_scan_info *info, int *i)
{
	if (info->data->line[*i] == '}' && info->end < info->begin)
		if (expansions_update_with_brace(info, *i, true) == ERR)
			return (ERR);
	if (ft_str_append(&info->data->buf, info->data->line[*i]) == ERR)
		return (free_n_return(&info->data->buf, ERR));
	return (OK);
}

static t_res	expansion_scan_loop(t_expansion_scan_info *info, int *i)
{
	t_res	res;

	while (is_scan_continuos(
			info->data->buf, info->data->line[++*i], info->data->type))
	{
		if (!is_brace_open(info->data->buf)
			&& !is_variable_char_valid(info->data->line[*i]))
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

static t_res	expansion_scan(t_list **list, t_scan_data *data)
{
	t_expansion_scan_info	info;
	int						i;
	t_list					*list_element;

	info.data = data;
	info.start_i = ft_strlen(data->buf);
	i = data->idx;
	if (!is_1stchar_valid(data->line[i + 1]))
		return (UNSET);
	info.expansions = new_ast_expansions((t_AST_expansion *[]){NULL});
	if (!info.expansions)
		return (free_n_return(&data->buf, ERR));
	if (expansion_location_init(&info, &i) == ERR)
		return (ERR);
	if (expansion_scan_loop(&info, &i) == ERR)
		return (ERR);
	if (list_element_create(&list_element, data->buf, info.expansions) == ERR)
		return (free_n_return(&data->buf, ERR));
	ft_list_append(list, list_element);
	data->idx = --i;
	return (OK);
}

t_res	dollar_scan(t_list **list, t_scan_data *data)
{
	char	last_quote;
	t_res	res;

	if (data->line[data->idx] == '$')
	{
		if (data->type == CMD && is_quotes_open(&last_quote, data->buf)
			&& last_quote == '\'')
			return (UNSET);
		res = expansion_scan(list, data);
		if (res == UNSET)
			return (UNSET);
		if (res == ERR)
			return (ERR);
		free(data->buf);
		data->buf = new_str("");
		if (!data->buf)
			return (ERR);
		return (OK);
	}
	return (UNSET);
}
