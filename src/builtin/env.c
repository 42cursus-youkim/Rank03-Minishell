#include "minishell.h"

int	builtin_env(t_context *context, t_shell *shell)
{
	(void)context;
	if (check_no_opt_arg(context->argv, "env") != OK)
		return (EXIT_FAILURE);
	env_print(shell->env);
	return (OK);
}
