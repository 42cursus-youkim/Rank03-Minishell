#include "minishell.h"

static void	test_exec(char **argv)
{
	if (execve(argv[0], argv, NULL) == OK)
		exit(0);
	printf(RED "Execve fail!\n" END);
	exit(1);
}

static void	api_pipe(char **argv, t_dict *env) // TODO: change to t_AST_COMMAND *cmd,
{
	(void)env;
	pid_t	pid;
	t_fd	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (is_child(pid))
	{
		send_output_to_pipe(pipefd);
		// api_exec(cmd, env);
		test_exec(argv);
	}
	if (is_parent(pid)) // is waiting for child
	{
		receive_input_from_pipe(pipefd);
		waitpid(pid, NULL, WAIT_CHILD_END);
	}
	else
		printf(RED "fork error\n" END);
}

t_res	api_exec_pipe(t_AST_PIPELINE *pipeline, t_dict *env)
{
	int	i;

	char **argvs[] = {
			(char *[]){"/usr/bin/ls", "-l", ".", NULL},
			(char *[]){"/usr/bin/wc", NULL},
			(char *[]){"/usr/bin/wc", NULL},
		};

	(void)env; (void)pipeline; (void)i;
	// i = -1;
	// while ()
	// {

	// }
	// test_exec(argvs[0]);
	i = 0;
	api_pipe(argvs[i], NULL);
	// i = 1;
	// test_exec(argvs[i]);
	// wait(0);
	return (OK);
}