#include "minishell.h"

static char	*new_target(
	t_context *context, t_shell *shell)
{
	char		*arg;
	char		*target;
	const int	argv_len = ft_arr_len(context->argv);

	if (argv_len == 1)
		return (new_str(env_get(shell->env, "HOME")));
	arg = context->argv[1];
	if (arg[0] == '~')
		return (new_path_resolved(arg, shell->env));
	else if (is_str_equal(arg, "-"))
		target = new_str(dict_get(shell->env, "OLDPWD"));
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
	target = new_target(context, shell);
	if (chdir(target) == ERR)
		error_syscall_with_arg("cd", target);
	free(target);
	cwd = new_cwd();
	dict_set(shell->env, "PWD", cwd);
	dict_set(shell->env, "OLDPWD", oldpwd);
	return (EXIT_SUCCESS);
}
