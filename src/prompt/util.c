#include "minishell.h"

void	prompt_exit(t_shell *shell)
{
	t_context	context;

	context_init(&context, shell->script->commands[0], shell->env);
	printf("exit\n");
	builtin_exit(&context, shell);
}

void	cursor_up(void)
{
	ft_write(1, "\033[1A");
}

// ctrl + d in heredoc readline
void	prompt_eof_heredoc(t_shell *shell)
{
	cursor_up();
	ft_write(STDOUT_FILENO, shell->prompt.ps2);
}

/*
	only works when replaced line is shorter than original prompt.
	intended to be only used with EOF
*/
void	prompt_replace_line_with(char *line, char *ps, char *new_line)
{
	cursor_up();
	printf("\r%s%s\n", ps, new_line);
	free(line);
}
