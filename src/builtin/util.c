#include "minishell.h"

t_builtin	which_builtin(char *str)
{
	int			i;
	const char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};

	i = -1;
	while (++i < 6)
		if (is_str_equal(builtins[i], str))
			return (i);
	return (ERR);
}

bool	is_builtin(char *str)
{
	return ((int)which_builtin(str) != ERR);
}

bool	is_opt(char *str)
{
	return (ft_strlen(str) > 1 && str[0] == '-');
}
