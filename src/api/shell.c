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

//	frees allocated memory from shell && exits with exitcode
void	api_exit(t_shell *shell, int exitcode)
{
	del_shell(shell);
	exit(exitcode);
}
