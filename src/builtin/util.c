#include "minishell.h"

t_builtin	which_builtin(const char *str)
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
	while (++i < 7)
		if (is_str_equal(builtins[i], str))
			return (i);
	return (ERR);
}

bool	is_builtin(const char *str)
{
	return ((int)which_builtin(str) != ERR);
}

bool	is_opt(char *str)
{
	return (ft_strlen(str) > 1 && str[0] == '-');
}

bool	is_exit(t_shell *shell)
{
	t_AST_SCRIPT	*script;

	script = shell->script;
	return (
		is_ast_command(script)
		&& which_builtin(script->commands[0]->name->text) == BUILTIN_EXIT);
}
