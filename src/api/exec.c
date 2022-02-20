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


}
*/

// FIXME: char *argv[] -> t_AST_COMMAND *cmd
void	api_raw_exec(char *argv[], t_dict *env)
{
	(void)env;

	printf(HYEL "HAYO I'm child\n" END);
	char *envp[] = {NULL};
	if (execve(argv[0], argv, envp) == OK)
		exit(0);
	printf(RED "Execve fail!\n" END);
	exit(1);
}

static int	parent_proc(pid_t pid)
{
	int	status;
	int	exitcode;

	printf(HGRN "HAYO I'm Parent process\n" END);
	waitpid(pid, &status, 0);
	exitcode = api_handle_status(status);
	if (exitcode == OK)
	{
		printf(BGRN "HAYO child is successfully dead!\n" END);
		return (OK);
	}
	else
	{
		printf(BRED "exitcode: %d\n" END, exitcode);
		return (exitcode);
	}
}

// TODO: change it to use t_AST_COMMAND *cmd, t_dict *env
t_res	api_exec_cmd(char **argv)
{
	pid_t	pid;

	pid = fork();

	if (is_child(pid))
		api_raw_exec(argv, NULL);
	else if (is_parent(pid))
	{
		parent_proc(pid);
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