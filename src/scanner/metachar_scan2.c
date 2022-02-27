#include "minishell.h"

t_res	metachar_attachable(char **pstr, char prev_c, char c)
{
	if (prev_c != '|' && ft_strlen(*pstr) == 1 && c == prev_c)
	{
		if (ft_str_append(pstr, c) == ERR)
			return (free_n_return(pstr, error_malloc_msg()));
		return (OK);
	}
	return (UNSET);
}

t_res	metastr_init(t_metastr *metastr, char c)
{
	metastr->str = new_str((char []){c, '\0'});
	if (!metastr->str)
		return (error_malloc_msg());
	metastr->prev = new_str("");
	if (!metastr->prev)
		return (free_n_return(&metastr->str, error_malloc_msg()));
	return (OK);
}

bool	is_prev_metachar_attachable(char *str)
{
	return (is_str_equal(str, "") || is_str_equal(str, "|"));
}
