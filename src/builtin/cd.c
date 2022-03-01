#include "minishell.h"

static char	*get_target(
	t_context *context, t_shell *shell)
{
	char		*arg;
	char		*target;
	const int	argv_len = ft_arr_len(context->argv);

	if (argv_len == 1)
		return (env_get(shell->env, "HOME"));
	arg = context->argv[1];
	if (is_str_equal(arg, "~"))
		return (env_get(shell->env, "HOME"));
	else if (is_str_equal(arg, "-"))
		target = dict_get(shell->env, "OLDPWD");
	else
		target = arg;
	return (target);
}

int	builtin_cd(t_context *context, t_shell *shell)
{
	char	*cwd;
	char	*oldpwd;
	char	*target;

	oldpwd = new_cwd();
	target = get_target(context, shell);
	if (chdir(target) == ERR)
		error_syscall_with_arg("cd", target);
	cwd = new_cwd();
	dict_set(shell->env, "PWD", cwd);
	dict_set(shell->env, "OLDPWD", oldpwd);
	return (EXIT_SUCCESS);
}
