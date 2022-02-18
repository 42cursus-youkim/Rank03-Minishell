#include "minishell.h"


static void	api_exec_cmd_inner(t_AST_COMMAND *cmd, t_dict *env)
{
	int		i;
	char	**envp;
	char	**names;
	(void)cmd;

	names = new_path_with_name(env, "ls"); //cmd->name.text);
	envp = new_arr_env(env);
	i = -1;
	while (names[++i])
		execve(names[i], (char *[]){"~", NULL}, envp);
	del_arr(envp);
}

static t_res	parent_proc(pid_t pid)
{
	int		status;

	printf("I'm parent and waiting for child\n");
	waitpid(pid, &status, WNOHANG);
	if (status == pid)
	{
		printf("child is successfully dead!\n");
		return (OK);
	}
	else
	{
		printf("something's gone wrong\n");
		return (ERR);
	}
}

static void	child_proc(t_AST_COMMAND *cmd, t_dict *env)
{
	printf("HAYO I'm child\n");
	api_exec_cmd_inner(cmd, env);
}

t_res	api_run_cmd(t_AST_COMMAND *cmd, t_dict *env)
{
	pid_t	pid;

	pid = fork();
	if (is_parent(pid))
		return (parent_proc(pid));
	else if (is_child(pid))
		child_proc(cmd, env);
	else
		printf(RED "fork error\n" END);
	return (ERR);
}

// t_res	api_run_pipe(t_AST_PIPELINE *pipeline, t_dict *env)
// {

// }