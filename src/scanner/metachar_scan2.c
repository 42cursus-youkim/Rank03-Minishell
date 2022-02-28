#include "minishell.h"

bool	is_metachar_attachable(char **pstr, char prev_c, char c)
{
	if (prev_c != '|' && ft_strlen(*pstr) == 1 && c == prev_c)
	{
		ft_str_append(pstr, c);
		return (true);
	}
	return (false);
}

bool	is_prev_metachar_attachable(char *str)
{
	return (is_str_equal(str, "") || is_str_equal(str, "|"));
}
