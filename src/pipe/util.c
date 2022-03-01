#include <unistd.h>
#include "minishell_type.h"
#include "pipe.h"

void	api_copy_pipe(t_fd from[PIPE_SIZE], t_fd to[PIPE_SIZE])
{
	to[PIPE_READ] = from[PIPE_READ];
	to[PIPE_WRITE] = from[PIPE_WRITE];
}

void	api_close_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
}

//	same with dup2 but with error handling
t_fd	api_dup2(t_fd from, t_fd to)
{
	int	res;

	res = dup2(from, to);
	if (res == ERR)
		error_syscall("dup2");
	return (res);
}

t_fd	api_dup(t_fd from)
{
	int	res;

	res = dup(from);
	if (res == ERR)
		error_syscall("dup");
	return (res);
}
