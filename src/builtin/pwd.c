#include "minishell.h"

int	builtin_pwd(t_context *context, t_shell *shell)
{
	if (check_no_opt_arg(context->argv, "pwd") != OK)
		return (EXIT_FAILURE);
	printf("%s\n", env_get(shell->env, "PWD"));
	return (EXIT_SUCCESS);
}
