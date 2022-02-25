#include "minishell.h"


t_res	api_exec_pipe_at(t_shell *shell, int index, int pids[])
{
	pid_t		pid;
	t_fd		pipefd[PIPE_SIZE];
	const int	len = shell->script->commands_len;

	pipe(pipefd);
	pid = fork();
	if (is_child(pid))
	{
		if (index < len - 1)
			send_output_to_pipe(pipefd);
		child_proc(shell, index);
		close(pipefd[PIPE_WRITE]);
	}
	else if (is_parent(pid))
	{
		pids[index] = pid;
		if (index < len -1)
			receive_input_from_pipe(pipefd);
	}
	else
		printf(RED "fork error\n" END);
	return (OK);
}

static void	api_exec_pipe_internal(t_shell *shell)
{
	int			i;
	int			*pids;
	int 		status;
	const int	len = shell->script->commands_len;

	pids = ft_calloc(sizeof(pid_t), len);
	i = -1;
	while (++i < len)
		api_exec_pipe_at(shell, i, pids);
	i = -1;
	while (++i < len)
		waitpid(pids[i], &status, 0);
	free(pids);
	api_exit(shell,
		api_handle_exitcode(shell->env, status));
}

int	api_exec_pipe(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (is_child(pid))
		api_exec_pipe_internal(shell);
	else if (is_parent(pid))
	{
		waitpid(pid, &status, 0);
		return (api_handle_exitcode(shell->env, status));
	}
	else
		printf(RED "fork error\n" END);
	return (ERR);
}
