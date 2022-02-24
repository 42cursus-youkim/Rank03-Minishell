#include "minishell.h"

t_res	expansions_update_with_brace(
	t_expansion_scan_info *info, int end, bool brace)
{
	char	*parameter;

	info->end = end - *info->idx + info->start_i;
	parameter = new_str_slice(*info->buf,
			info->begin + 1 + brace, info->end + 1 - brace);
	if (!parameter)
		return (free_n_return(info->buf, error_malloc_msg()));
	if (expansions_append_free(&info->expansions,
			new_ast_expansion(parameter, info->begin, info->end)) == ERR)
		return (free_arr_n_return((char *[]){*info->buf, parameter, NULL},
			error_malloc_msg()));
	free(parameter);
	return (OK);
}

t_res	expansion_location_init(t_expansion_scan_info *info, int *i)
{
	info->begin = *i - *info->idx + info->start_i;
	if (ft_str_extend(info->buf, (char []){'$', info->str[++*i], '\0'}) == ERR)
		return (free_n_return(info->buf, error_malloc_msg()));
	info->end = -1;
	if (info->str[*i] == '?')
		if (expansions_update_with_brace(info, *i, false) == ERR)
			return (ERR);
	return (OK);
}

bool	is_multi_expansions(t_expansion_scan_info info, int i)
{
	char	last_quote;

	if (info.str[i] == '$' && is_1stchar_valid(info.str[i + 1])
		&& (!is_quotes_open(&last_quote, *info.buf) || last_quote != '\'')
		&& !is_brace_open(*info.buf))
		return (true);
	return (false);
}
