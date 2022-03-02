#include "minishell.h"

static	t_res	write_to_heredoc_and_free(t_fd fd, char *str)
{
	int	res;

	res = ft_writes(fd, (char *[]){str, "\n", NULL});
	ft_free(str);
	if (res == ERR)
		return (ERR);
	return (OK);
}

static t_res	process_heredoc(
	t_shell *shell, t_fd pipefd[PIPE_SIZE], char **pstr)
{
	if (replace_line_heredoc(pstr, shell->env) == ERR)
	{
		close(pipefd[PIPE_READ]);
		return (ERR);
	}
	return (write_to_heredoc_and_free(pipefd[PIPE_WRITE], *pstr));
}

static t_res	shell_heredoc_inner(
	t_shell *shell, t_fd pipefd[PIPE_SIZE], const char *eof)
{
	char	*line;

	line = readline(shell->prompt.ps2);
	if (!line)
	{
		prompt_eof_heredoc(shell);
		return (UNSET);
	}
	else if (is_str_equal(line, eof))
	{
		ft_free(line);
		return (UNSET);
	}
	else if (is_line_empty(line))
	{
		write_to_heredoc_and_free(pipefd[PIPE_WRITE], line);
		return (OK);
	}
	else
		return (process_heredoc(shell, pipefd, &line));
}

/*	get input for heredoc
	returns opened fd that points to it
*/
t_fd	shell_heredoc(t_shell *shell, const char *eof)
{
	t_res	res;
	t_fd	pipefd[PIPE_SIZE];

	if (pipe(pipefd) == ERR)
		return (ERR);
	res = OK;
	while (res == OK)
		res = shell_heredoc_inner(shell, pipefd, eof);
	if (res == ERR)
	{
		api_close_pipe(pipefd);
		return (ERR);
	}
	else
	{
		close(pipefd[PIPE_WRITE]);
		return (pipefd[PIPE_READ]);
	}
}
