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
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (is_child(pid))
	{
		close(pipefd[PIPE_READ]);
		dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
		// api_exec(cmd, env);
		test_exec(argv);
	}
	else if (is_parent(pid)) // is waiting for child
	{
		close(pipefd[PIPE_WRITE]);
		dup2(pipefd[PIPE_READ], STDIN_FILENO);
		waitpid(pid, NULL, WAIT_CHILD_END);
	}
	else
		printf(RED "fork error\n" END);
}

t_res	api_exec_pipe(t_AST_PIPELINE *pipeline, t_dict *env)
{
	int	i;

	char **argvs[] = {
			(char *[]){"usr/bin/ls", "-l", "/home/scarf/Repo", NULL},
			(char *[]){"/usr/bin/wc", NULL},
			(char *[]){"/usr/bin/wc", NULL},
		};

	(void)env; (void)pipeline;
	// i = -1;
	// while ()
	// {

	// }
	for (i = 0; i < 2; i++)
	{
		api_pipe(argvs[i], NULL);
	}
	test_exec(argvs[i]);
	wait(0);
	return (OK);
}