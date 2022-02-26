#include "minishell.h"

t_res	expansions_update_with_brace(
	t_expansion_scan_info *info, int end, bool brace)
{
	char	*parameter;

	info->end = end - info->data->idx + info->start_i;
	parameter = new_str_slice(info->data->buf,
			info->begin + 1 + brace, info->end + 1 - brace);
	if (!parameter)
		return (free_n_return(&info->data->buf, error_malloc_msg()));
	if (expansions_append_free(&info->expansions,
			new_ast_expansion(parameter, info->begin, info->end)) == ERR)
		return (free_arr_n_return((char *[]){info->data->buf, parameter, NULL},
			error_malloc_msg()));
	free(parameter);
	return (OK);
}

t_res	expansion_location_init(t_expansion_scan_info *info, int *i)
{
	info->begin = *i - info->data->idx + info->start_i;
	if (ft_str_extend(&info->data->buf,
			(char []){'$', info->data->line[++*i], '\0'}) == ERR)
		return (free_n_return(&info->data->buf, error_malloc_msg()));
	info->end = -1;
	if (info->data->line[*i] == '?')
		if (expansions_update_with_brace(info, *i, false) == ERR)
			return (ERR);
	return (OK);
}

bool	is_multi_expansions(t_expansion_scan_info info, int i)
{
	char	last_quote;

	if (info.data->line[i] == '$' && is_1stchar_valid(info.data->line[i + 1])
		&& (!is_quotes_open(&last_quote, info.data->buf) || last_quote != '\'')
		&& !is_brace_open(info.data->buf))
		return (true);
	return (false);
}
