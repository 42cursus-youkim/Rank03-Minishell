#include "minishell.h"

/* FIXME:
	char *argv[]
	-> t_AST_COMMAND *cmd, t_dict *env
*/
static void	api_pipe_temp(char **argv)
{
	pid_t	pid;
	t_fd	pipefd[PIPE_SIZE];

	pipe(pipefd);
	pid = fork();
	if (is_child(pid))
	{
		send_output_to_pipe(pipefd);
		api_raw_exec_temp(argv, NULL);
	}
	if (is_parent(pid))
	{
		receive_input_from_pipe(pipefd);
		waitpid(pid, NULL, WAIT_UNTIL_CHILD_END);
	}
	else
		printf(RED "fork error\n" END);
}

/* FIXME:
	int size, char **argvs[]
	-> t_AST_PIPELINE *pipeline, t_dict *env
*/
t_res	api_exec_pipe_temp(int size, char **argvs[])
{
	int	i;

	i = -1;
	while (++i < size - 1)
		api_pipe_temp(argvs[i]);
	api_exec_cmd_temp(argvs[i]);
	printf(BGRN "HAYO all pipe process finished\n" END);
	return (OK);
}
