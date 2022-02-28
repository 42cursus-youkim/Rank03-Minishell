#include "minishell.h"

/*	pids are malloced and then forked,
	therefore must be freed INSIDE CHILD process  too
*/
// t_res	api_exec_pipe_at(
// 	t_shell *shell, int index, int pids[],
// 	t_fd prev[PIPE_SIZE], t_fd next[PIPE_SIZE])
// {
// 	pid_t		pid;
// 	const int	len = shell->script->commands_len; (void)len;

// 	if (has_pipe_next(index, len))
// 		if (pipe(next) == ERR)
// 			return (error_msg_category("pipe", "failed to create pipe"));
// 	pid = fork();
// 	if (is_child(pid))
// 	{
// 		free(pids);
// 		if(has_pipe_prev(index))
// 		{
// 			receive_input_from_pipe(pipefd);
// 		}
// 		else if (has_pipe_next(index, len))
// 			send_output_to_pipe(pipefd);
// 		// else
// 			// api_close_pipe(pipefd);
// 		child_proc(shell, index);
// 	}
// 	else if (is_parent(pid))
// 	{
// 		pids[index] = pid;
// 		if (has_pipe_next(index, len))
// 			receive_input_from_pipe(pipefd);
// 		// else
// 		// 	api_close_pipe(pipefd);
// 	}
// 	else
// 		return (error_msg_category("fork", "failed to create fork"));
// 	return (OK);
// }
/*
prev[3, 4]
next[5, 6]


*/
int	api_exec_pipe(t_shell *shell)
{
	int			i;
	int			*pids;
	int			status;
	t_fd		prev[PIPE_SIZE];
	t_fd		next[PIPE_SIZE];
	const int	len = shell->script->commands_len;

	pids = ft_calloc(sizeof(pid_t), len);
	i = -1;
	while (++i < len)
	{
		if (has_pipe_next(i, len))
			if (pipe(next) == ERR)
				return (error_msg_category("pipe", "failed to create pipe"));
		pids[i] = fork();
		if (is_child(pids[i]))
		{
			if (has_pipe_prev(i))
				receive_input_from_pipe(prev);
			if (has_pipe_next(i, len))
				send_output_to_pipe(next);
			child_proc(shell, i);
		}
		else if (is_parent(pids[i]))
		{
			if (has_pipe_prev(i))
				api_close_pipe(prev);
			if (has_pipe_next(i, len))
				api_copy_pipe(next, prev);
		}
	}
			// api_exec_pipe_at(shell, i, pids, &prev, &next);
	i = -1;
	while (++i < len)
		waitpid(pids[i], &status, 0);
	free(pids);
	return (api_handle_exitcode(shell->env, status));
	return (ERR);
}
