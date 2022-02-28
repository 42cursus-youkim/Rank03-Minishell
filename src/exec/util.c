#include "minishell.h"

bool	is_parent(pid_t pid)
{
	return (pid > 0);
}

bool	is_child(pid_t pid)
{
	return (pid == 0);
}

bool	has_pipe_prev(int index)
{
	return (index > 0);
}

bool	has_pipe_next(int index, int length)
{
	return (index < length - 1);
}

void	send_output_to_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_READ]);
	api_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close(pipefd[PIPE_WRITE]);
}

void	receive_input_from_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_WRITE]);
	api_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close(pipefd[PIPE_READ]);
}

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

void	api_dup2(t_fd from, t_fd to)
{
	fprintf(stderr, BYEL "from:%d to:%d\n" END, from, to);
	int res = dup2(from, to);
	fprintf(stderr, "dup2 result: %d\n", res);
	if (res == ERR)
		error_syscall("dup2");
}
