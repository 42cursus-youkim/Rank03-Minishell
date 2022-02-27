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

int	shell_exec_script(t_shell *shell)
{
	int	exitcode;

	exitcode = EXIT_FAILURE;
	shell_open_redirects(shell);
	if (is_ast_command(shell->script))
		exitcode = api_exec_cmd_at(shell, 0);
	else if (is_ast_pipeline(shell->script))
		exitcode = api_exec_pipe(shell);
	if (DEBUG && exitcode != OK)
		printf(BRED "exitcode: %d\n" END, exitcode);
	return (exitcode);
}

void	shell_init(t_shell *shell, char *envp[])
{
	shell->env = new_env(envp);
	shell->script = NULL;
	prompt_init(&shell->prompt);
}

void	del_shell(t_shell *shell)
{
	del_env(shell->env);
	del_prompt(&shell->prompt);
	shell_clear_script(shell);
}
