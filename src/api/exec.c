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

bool	is_parent(pid_t pid)
{
	return (pid > 0);
}

void	api_exec_cmd(t_AST_COMMAND *cmd, t_dict *env)
{
	pid_t	pid;
	(void)cmd; (void)env;

	pid = fork();
	if (is_parent(pid))
	{
		printf("I'm parent and waiting for child\n");
		// close(pipe[PIPE_WRITE]);
		// dup2(pipe[PIPE_READ], STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
		printf("yo child's dead\n");
	}
	else if (pid == CHILD)
	{
		// close(pipe[PIPE_READ]);
		printf("HAYO I'm child\n");
		api_exec_cmd_inner(cmd, env);
	}
	else
		printf("fork error\n");
}
