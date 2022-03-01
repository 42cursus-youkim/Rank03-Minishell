#include "minishell.h"

static void	pipe_child_at(
	t_pipe_context *context, int i, const int len, t_shell *shell)
{
	free(context->pids);
	if (has_pipe_prev(i))
		api_receive_input_from_pipe(context->prev);
	if (has_pipe_next(i, len))
		api_send_output_to_pipe(context->next);
	child_proc(shell, i);
}

static void	pipe_parent_at(
	t_pipe_context *context, int i, const int len)
{
	if (has_pipe_prev(i))
		api_close_pipe(context->prev);
	if (has_pipe_next(i, len))
		api_copy_pipe(context->next, context->prev);
}

int	api_exec_pipe(t_shell *shell, const int len)
{
	int				i;
	int				status;
	t_pipe_context	context;

	context.pids = ft_calloc(sizeof(pid_t), len);
	i = -1;
	while (++i < len)
	{
		if (has_pipe_next(i, len))
			if (api_create_pipe(context.next) == ERR)
				free_n_return(context.pids, EXIT_FAILURE);
		context.pids[i] = fork();
		if (is_child(context.pids[i]))
			pipe_child_at(&context, i, len, shell);
		else if (is_parent(context.pids[i]))
			pipe_parent_at(&context, i, len);
		else
			error_syscall("fork");
	}
	status = wait_pipe_processes(context.pids, len);
	free(context.pids);
	return (api_handle_exitcode(shell->env, status));
}
