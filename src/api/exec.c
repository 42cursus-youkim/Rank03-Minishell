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
	// int	exitcode;

	// printf(GRN "I'm parent and waiting for child\n" END);
	// waitpid(pid, &status, WNOHANG);
	// exitcode = api_handle_status(status);
	// if (exitcode == OK)
	// {
	// 	printf(GRN "child is successfully dead!\n" END);
	// 	return (OK);
	// }
	// else
	// {
	// 	printf(BRED "exitcode: %d\n" END, exitcode);
	// 	return (ERR);
	// }

}
*/

static void	child_proc(t_AST_COMMAND *cmd, t_dict *env)
{
	(void)env; (void)cmd;

	printf(HYEL "HAYO I'm child\n" END);
	char *argv[] = {"/bin/ls", "-l", "/home/scarf/Repo", NULL};
	char *envp[] = {NULL};
	if (execve(argv[0], argv, envp) == -1)
		printf("execve failed\n");
	exit(0);
}

// static void	parent_proc(pid_t pid)
// {
// 	int	status;
// 	printf(HGRN "HAYO I'm Parent process\n" END);
// 	waitpid(pid, &status, WNOHANG);
// 	printf ("Child process exited with status %d\n", api_handle_status(status));
// }

t_res	api_exec_cmd(t_AST_COMMAND *cmd, t_dict *env)
{
	pid_t	pid;

	(void)env; (void)cmd;

	pid = fork();

	if (is_child(pid))
	{
		child_proc(NULL, NULL);
		// char *argv[] = {"/bin/ls", "-l", "/home/scarf/Repo", NULL};
		// char *envp[] = {NULL};
		// if (execve(argv[0], argv, envp) == -1)
		// 	printf("execve failed\n");
	}
	else if (is_parent(pid))
	{
		// parent_proc(pid);
		int	status;
		printf(HGRN "HAYO I'm Parent process\n" END);
		waitpid(pid, &status, WNOHANG);
		printf ("Child process exited with status %d\n", api_handle_status(status));
		return (OK);
	}
	else
		printf(RED "fork error\n" END);
	return (OK);
	// if (is_parent(pid))
	// 	return (parent_proc(pid));
	// else if (is_child(pid))
	// 	return (child_proc(cmd, env));
	// else
	// return (ERR);
}

// t_res	api_run_pipe(t_AST_PIPELINE *pipeline, t_dict *env)
// {
// }