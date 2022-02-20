#include "minishell.h"

/* FIXME:
	char *argv[]
	-> t_AST_COMMAND *cmd, t_dict *env
*/
void	api_raw_exec_temp(char *argv[], t_dict *env)
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

/* FIXME:
	char *argv[]
	-> t_AST_COMMAND *cmd, t_dict *env
*/
t_res	api_exec_cmd_temp(char *argv[])
{
	pid_t	pid;

	pid = fork();

	if (is_child(pid))
		api_raw_exec_temp(argv, NULL);
	else if (is_parent(pid))
	{
		parent_proc(pid);
		return (OK);
	}
	else
		printf(RED "fork error\n" END);
	return (OK);
}
