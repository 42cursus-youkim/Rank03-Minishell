#include "minishell.h"

/*	get input for heredoc
	returns opened fd that points to it
*/
t_fd	shell_heredoc(char *ps, const char *eof)
{
	char	*line;
	t_fd	pipefd[PIPE_SIZE];

	if (pipe(pipefd) == ERR)
		return (ERR);
	while (true)
	{
		line = readline(ps);
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
}
