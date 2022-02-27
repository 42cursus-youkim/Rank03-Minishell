#include "minishell.h"

bool	is_line_eof(char *line)
{
	return (line == NULL);
}

bool	is_line_empty(char *line)
{
	return (ft_strlen(line) <= 0);
}

void	prompt_exit(t_shell *shell)
{
	printf("exit\n");
	api_exit(shell, shell->env->exitcode);
}

void	cursor_up(void)
{
	ft_write(1, "\033[1A");
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
