#include "minishell.h"

int	builtin_cd(t_context *context, t_shell *shell)
{
	if (check_no_opt(context->argv, "cd") != OK
		|| check_arg_no_more_than(context->argv, "cd", 1) != OK)
		return (EXIT_FAILURE);
	if (chdir(context->argv[1]) == ERR)
		error_syscall("cd");
	dict_set(shell->env, "PWD", getcwd(NULL, 0));
	return (OK);
}
