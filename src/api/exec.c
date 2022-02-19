#include "minishell.h"
/*
static void	api_exec_cmd_inner(t_AST_COMMAND *cmd, t_dict *env)
{
	int		i;
	// char	**envp;
	char	*name = "/usr/bin/echo";
	// char	**names;
	(void)cmd; (void)env; (void)i;

	char *argv[] = {name, "..", NULL};
	char *envp[] = {NULL};
	// envp = new_arr_env(env);
	if (execve(name, argv, envp) == ERR)
	{
		perror("execve");
		printf(RED "execve failed\n" END);
	}
	// names = new_path_with_name(env, name);
	// i = -1;
	// while (names[++i])
	// 	execve(names[i], (char *[]){"..", NULL}, envp);
	// del_arr(envp);
}

static t_res	parent_proc(pid_t pid)
{
	int	status;
	int	exitcode;

	printf(GRN "I'm parent and waiting for child\n" END);
	waitpid(pid, &status, WNOHANG);
	exitcode = api_handle_status(status);
	if (exitcode == OK)
	{
		printf(GRN "child is successfully dead!\n" END);
		return (OK);
	}
	else
	{
		printf(BRED "exitcode: %d\n" END, exitcode);
		return (ERR);
	}
}

static int	child_proc(t_AST_COMMAND *cmd, t_dict *env)
{
	printf("HAYO I'm child\n");
	api_exec_cmd_inner(cmd, env);
	return (0);
}
*/
t_res	api_exec_cmd(t_AST_COMMAND *cmd, t_dict *env)
{
	pid_t	pid;

	(void)env; (void)cmd;
	pid = fork();

	if (is_child(pid))
	{
		printf("Child process\n");
		char *argv[] = {"/bin/ls", "-l", NULL};
		char *envp[] = {NULL};
		if (execve(argv[0], argv, envp) == -1)
			printf("execve failed\n");
	}
	else if (is_parent(pid))
	{
		printf("Parent process\n");
		int status;
		waitpid(pid, &status, WNOHANG);
		printf ("Child process exited with status %d\n", api_handle_status(status));
  	}
	return (OK);
	// if (is_parent(pid))
	// 	return (parent_proc(pid));
	// else if (is_child(pid))
	// 	return (child_proc(cmd, env));
	// else
	// 	printf(RED "fork error\n" END);
	// return (ERR);
}

// t_res	api_run_pipe(t_AST_PIPELINE *pipeline, t_dict *env)
// {
// }