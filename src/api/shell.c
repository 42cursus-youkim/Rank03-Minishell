#include "minishell.h"

void	shell_init(t_shell *shell, char *envp[])
{
	shell->env = new_env(envp);
	shell->exitcode = EXIT_SUCCESS;
	prompt_init(&shell->prompt);
}

void	del_shell(t_shell *shell)
{
	del_dict(shell->env);
	del_prompt(&shell->prompt);
}

void	api_exit(t_shell *shell, int exitcode)
{
	del_shell(shell);
	exit(exitcode);
}
