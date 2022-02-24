#include "minishell.h"

/*	get input for heredoc
	returns opened fd that points to it
*/
t_fd	shell_heredoc(t_shell *shell, char *eof)
{
	char	*line;
	t_fd	pipefd[PIPE_SIZE];

	pipe(pipefd);
	while (true)
	{
		line = readline(shell->prompt.ps2);
		if (is_str_equal(line, eof))
		{
			free(line);
			break ;
		}
		else
		{
			ft_writes(pipefd[PIPE_WRITE], (char *[]){line, "\n", NULL});
			free(line);
		}
	}
	close(pipefd[PIPE_WRITE]);
	return (pipefd[PIPE_READ]);
	// dup2(pipefd[0], STDIN_FILENO); <- use to connect
}