#include "minishell.h"

// ctrl + d in heredoc readline
static void	eof_heredoc(t_shell *shell)
{
	cursor_up();
	ft_write(1, shell->prompt.ps2);
}

static t_res	process_heredoc(t_shell *shell, t_fd fd, char **pstr)
{
	if (replace_line_heredoc(pstr, shell->env) == ERR)
		return (ERR);
	ft_writes(fd, (char *[]){*pstr, "\n", NULL});
	free(*pstr);
	return (OK);
}

/*	get input for heredoc
	returns opened fd that points to it
*/
t_fd	shell_heredoc(t_shell *shell, const char *eof)
{
	char	*line;
	t_fd	pipefd[PIPE_SIZE];

	if (pipe(pipefd) == ERR)
		return (ERR);
	while (true)
	{
		line = readline(shell->prompt.ps2);
		if (!line)
		{
			eof_heredoc(shell);
			break ;
		}
		else if (is_str_equal(line, eof))
			break ;
		else
			if (process_heredoc(shell, pipefd[PIPE_WRITE], &line) == ERR)
				break ;
	}
	if (line)
		free(line);
	close(pipefd[PIPE_WRITE]);
	return (pipefd[PIPE_READ]);
}
