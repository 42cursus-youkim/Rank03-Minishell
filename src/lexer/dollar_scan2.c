#include "minishell.h"

t_res	expansions_update_with_brace(
	t_expansion_scan_info *info, int end, bool brace)
{
	char	*parameter;

	info->end = end - *info->idx + info->start_i;
	parameter = new_str_slice(*info->buf,
			info->begin + 1 + brace, info->end + 1 - brace);
	if (!parameter)
		return (free_n_return(info->buf, error_msg_return(MALLOC_ERROR_MSG)));
	if (expansions_append_free(&info->expansions,
			new_ast_expansion(parameter, info->begin, info->end)) == ERR)
		return (free_arr_n_return((char *[]){*info->buf, parameter, NULL},
			error_msg_return(MALLOC_ERROR_MSG)));
	free(parameter);
	return (OK);
}

t_res	expansion_location_init(t_expansion_scan_info *info, int *i)
{
	info->begin = *i - *info->idx + info->start_i;
	if (ft_str_extend(info->buf, (char []){'$', info->str[++*i], '\0'}) == ERR)
		return (free_n_return(info->buf, error_msg_return(MALLOC_ERROR_MSG)));
	info->end = -1;
	return (OK);
}
