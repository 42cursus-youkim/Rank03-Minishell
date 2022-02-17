#include "minishell.h"

bool	is_builtin(char *str)
{
	int			i;
	const char	*builtins[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"setenv",
		"unset",
	};

	i = -1;
	while (++i < 6)
		if (is_str_equal(builtins[i], str))
			return (true);
	return (false);
}
