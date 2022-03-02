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

static t_res	process_heredoc(t_shell *shell, t_fd fd, char **pstr)
{
	if (replace_line_heredoc(pstr, shell->env) == ERR)
		return (ERR);
	return (write_to_heredoc_and_free(fd, *pstr));
}

static void	shell_heredoc_loop(
	t_shell *shell, t_fd pipefd[PIPE_SIZE], const char *eof)
{
	char	*line;

	while (true)
	{
		line = readline(shell->prompt.ps2);
		if (!line)
			return (prompt_eof_heredoc(shell));
		else if (is_str_equal(line, eof))
			return (ft_free(line));
		else if (is_str_equal(line, ""))
			write_to_heredoc_and_free(pipefd[PIPE_WRITE], line);
		else if (process_heredoc(shell, pipefd[PIPE_WRITE], &line) == ERR)
			return ;
	}
}

/*	get input for heredoc
	returns opened fd that points to it
*/
t_fd	shell_heredoc(t_shell *shell, const char *eof)
{
	t_fd	pipefd[PIPE_SIZE];

	if (pipe(pipefd) == ERR)
		return (ERR);
	shell_heredoc_loop(shell, pipefd, eof);
	close(pipefd[PIPE_WRITE]);
	return (pipefd[PIPE_READ]);
}
