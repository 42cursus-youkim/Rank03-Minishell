#include "minishell.h"

// FIXME: char *argv[] -> t_AST_COMMAND *cmd
static void	api_pipe(char **argv, t_dict *env)
{
	(void)env;
	pid_t	pid;
	t_fd	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (is_child(pid))
	{
		send_output_to_pipe(pipefd);
		api_raw_exec(argv, NULL);
	}
	if (is_parent(pid))
	{
		receive_input_from_pipe(pipefd);
		waitpid(pid, NULL, WAIT_CHILD_END);
	}
	else
		printf(RED "fork error\n" END);
}

/* FIXME:
	int size, char **argvs[]
	-> t_AST_PIPELINE *pipeline, t_dict *env
*/
t_res	api_exec_pipe(int size, char **argvs[])
{
	int	i;

	i = -1;
	while (++i < size - 1)
		api_pipe(argvs[i], NULL);
	api_exec_cmd(argvs[i]);
	printf(BGRN "HAYO all pipe process finished\n" END);
	return (OK);
}
