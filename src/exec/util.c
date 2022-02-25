#include "minishell.h"

bool	is_parent(pid_t pid)
{
	return (pid > 0);
}

bool	is_child(pid_t pid)
{
	return (pid == 0);
}

void	send_output_to_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_READ]);
	dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close(pipefd[PIPE_WRITE]);
}

void	receive_input_from_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_WRITE]);
	dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close(pipefd[PIPE_READ]);
}

