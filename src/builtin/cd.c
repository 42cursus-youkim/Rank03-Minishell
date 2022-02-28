#include "minishell.h"

static char	*get_target(t_context *context, t_shell *shell)
{
	char	*target;

	if (is_str_equal(context->argv[1], "-"))
		target = dict_get(shell->env, "OLDPWD");
	else
		target = context->argv[1];
	return (target);
}

int	builtin_cd(t_context *context, t_shell *shell)
{
	char	*cwd;
	char	*oldpwd;

	if (check_arg_no_more_than(context->argv, "cd", 1) != OK)
		return (EXIT_FAILURE);
	oldpwd = new_cwd();
	if (!oldpwd)
		return (EXIT_FAILURE);
	if (chdir(get_target(context, shell)) == ERR)
		error_syscall("chdir");
	cwd = new_cwd();
	if (!cwd)
		return (EXIT_FAILURE);
	dict_set(shell->env, "PWD", cwd);
	dict_set(shell->env, "OLDPWD", oldpwd);
	return (EXIT_SUCCESS);
}
