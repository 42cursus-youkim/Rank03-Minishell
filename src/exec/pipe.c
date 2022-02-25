#include "minishell.h"

t_res	api_exec_pipe_at(t_shell *shell, int index)
{
	pid_t	pid;
	t_fd	pipefd[PIPE_SIZE];

	pipe(pipefd);
	pid = fork();
	if (is_child(pid))
	{
		send_output_to_pipe(pipefd);
		child_proc(shell, index);
	}
	else if (is_parent(pid))
	{
		receive_input_from_pipe(pipefd);
		return (parent_proc(pid, shell->env));
	}
	else
		printf(RED "fork error\n" END);
	return (OK);
}

int	api_exec_pipe(t_shell *shell)
{
	int			i;
	pid_t		pid;
	int			exitcode;
	t_fd		pipefd[PIPE_SIZE];
	const int	len = shell->script->commands_len;

	pipe(pipefd);
	pid = fork();
	if (is_child(pid))
	{
		i = -1;
		while (++i < len - 1)
			api_exec_pipe_at(shell, i);
		exitcode = api_exec_cmd_at(shell, i);
		api_exit(shell, exitcode);
	}
	else if (is_parent(pid))
		return (parent_proc(pid, shell->env));
	else
		printf(RED "fork error\n" END);
	return (ERR);
}
