#include "minishell.h"

bool	is_builtin(char *str)
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
			return (true);
	return (false);
}
