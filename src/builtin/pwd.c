#include "minishell.h"

void	builtin_pwd(t_context *context, t_shell *shell)
{
	if (check_no_opt_arg(context->argv, "pwd") != OK)
		return ;
	printf("%s\n", env_get(shell->env, "PWD"));
}
