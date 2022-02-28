#include "minishell.h"

void	prompt_init(t_shell *shell)
{
	rl_catch_signals = 0;
	prompt_handle_signal();
	shell->prompt.ps1 = new_str("");
	shell->prompt.ps2 = new_str_join((char *[]){
			BBLU "> " END, NULL}, '\0');
	prompt_refresh_ps(shell);
}

/*
	- prompt: not freed; uses static allocation (init)
	- user: stores result of getenv(); should not be freed
	- ps1, ps2: freed
*/
void	del_prompt(t_prompt *prompt)
{
	free(prompt->ps1);
	free(prompt->ps2);
}

static void	prompt_process_line(char *line, t_shell *shell)
{
	t_token			*tokens;
	t_AST_SCRIPT	*script;

	tokens = new_tokens_from_line(line, shell->env);
	free(line);
	if (!tokens)
		return ;
	script = new_script_from_tokens(tokens);
	if (!script)
		return (env_set_exitcode(shell->env, EXIT_FAILURE));
	if (expander(script, shell->env) == ERR)
		return (env_set_exitcode(shell->env, EXIT_FAILURE));
	shell_replace_script(shell, script);
}

static void	shell_run_line(t_shell *shell)
{
	if (DEBUG)
		ast_script_repr(shell->script);
	if (!shell->script)
		return ;
	prompt_ignore_signal();
	if (is_exit(shell))
		prompt_exit(shell);
	else
		shell_exec_script(shell);
	prompt_refresh_ps(shell);
	prompt_handle_signal();
	shell_clear_script(shell);
}

void	shell_prompt(t_shell *shell)
{
	char		*line;
	t_prompt	*prompt;

	prompt = &shell->prompt;
	line = prompt->line;
	while (true)
	{
		line = readline(prompt->ps1);
		if (is_line_eof(line))
			return (prompt_replace_line_with(line, prompt->ps1, "exit"));
		else if (!is_line_empty(line))
		{
			add_history(line);
			prompt_process_line(line, shell);
			shell_run_line(shell);
		}
	}
}
