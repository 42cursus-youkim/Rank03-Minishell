#include "minishell.h"

static t_res	expansions_update(t_expansion_scan_info *info, int end)
{
	char	*parameter;

	info->end = end - *info->idx + info->start_i;
	parameter = new_str_slice(*info->buf, info->begin + 1, info->end + 1);
	expansions_append_free(&info->expansions,
		new_ast_expansion(parameter, info->begin, info->end));
	free(parameter);
	return (OK);
}

static t_res	expansion_location_init(t_expansion_scan_info *info, int *i)
{
	info->begin = *i - *info->idx + info->start_i;
	ft_str_extend(info->buf, (char []){'$', info->str[++*i], '\0'});
	info->end = -1;
	return (OK);
}

static t_res	expansion_scan_loop(t_expansion_scan_info *info, int *i)
{
	while (is_scan_continuos(*info->buf, info->str[++*i]))
	{
		if (!is_variable_char_valid(info->str[*i]))
		{
			if (info->end < info->begin)
				expansions_update(info, *i - 1);
			if (is_multi_expansions(*info, *i)
				&& expansion_location_init(info, i) == OK)
				continue ;
		}
		ft_str_append(info->buf, info->str[*i]);
	}
	if (info->end < info->begin)
		expansions_update(info, *i - 1);
	return (OK);
}

t_res	expansion_scan(t_list **list, char **buf, char *str, int *idx)
{
	t_expansion_scan_info	info;
	int						i;

	info.buf = buf;
	info.str = str;
	info.idx = idx;
	info.expansions = new_ast_expansions((t_AST_expansion *[]){NULL});
	info.start_i = ft_strlen(*buf);
	i = *info.idx;
	if (!is_1stchar_valid(str[i + 1]))
		return (UNSET);
	expansion_location_init(&info, &i);
	expansion_scan_loop(&info, &i);
	ft_list_append(list, new_list(
			new_scan_node(new_str(*info.buf), info.expansions)));
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
		*idx = i;
		free(*buf);
		*buf = new_str("");
		return (OK);
	}
	return (UNSET);
}
