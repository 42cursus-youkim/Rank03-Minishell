#include "minishell.h"

void	shell_clear_script(t_shell *shell)
{
	if (!shell->script)
		return ;
	del_ast_script(shell->script);
	shell->script = NULL;
}

void	shell_replace_script(t_shell *shell, t_AST_SCRIPT *script)
{
	shell_clear_script(shell);
	shell->script = script;
}

void	shell_reconnect_io(t_shell *shell)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	api_dup2(shell->io_backup[STDIN_FILENO], STDIN_FILENO);
	api_dup2(shell->io_backup[STDOUT_FILENO], STDOUT_FILENO);
}

int	shell_exec_script(t_shell *shell)
{
	int	exitcode;

	exitcode = EXIT_FAILURE;
	shell_open_redirects(shell);
	exitcode = shell->env->exitcode;
	if (is_ast_command(shell->script))
		exitcode = api_exec_cmd_at(shell, 0);
	else if (is_ast_pipeline(shell->script))
		exitcode = api_exec_pipe(shell);
	shell_reconnect_io(shell);
	if (DEBUG && exitcode != OK)
		printf(BRED "exitcode: %d\n" END, exitcode);
	return (exitcode);
}
