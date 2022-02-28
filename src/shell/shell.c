#include "minishell.h"

t_res	shell_init(t_shell *shell, char *envp[])
{
	shell->env = new_env(envp);
	if (!shell->env)
		return (ERR);
	shell->script = NULL;
	shell->io_backup[INPUT] = dup(STDIN_FILENO);
	shell->io_backup[OUTPUT] = dup(STDOUT_FILENO);
	prompt_init(shell);
	return (OK);
}

void	del_shell(t_shell *shell)
{
	del_env(shell->env);
	del_prompt(&shell->prompt);
	shell_clear_script(shell);
	close(shell->io_backup[INPUT]);
	close(shell->io_backup[OUTPUT]);
}
