#include "minishell.h"

// char	**new_command_to_argv(t_AST_COMMAND *cmd)
// {
// 	int	i;

// 	i = -1;
// }

static void	child_proc(t_AST_SCRIPTS *pipeline, t_shell *shell)
{
	// t_AST_COMMAND	*cmd;
	// char			**envp;
	char			*executable;

	// cmd = pipeline->commands[0];
	// envp = new_env_to_envp(shell->env);
	printf(HYEL "HAYO I'm child\n" END);
	executable = new_executable_from_env("ls", shell->env);
	printf("%s\n", executable);
	execve(executable, (char *[]){NULL}, (char *[]){NULL});
	free(executable);
	del_ast_pipeline(pipeline);
	printf(BYEL "Hmmmmmmm\n" END);
	api_exit(shell, EXIT_SUCCESS);
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

int	api_exec_cmd(t_AST_SCRIPTS *pipeline, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (is_child(pid))
		child_proc(pipeline, shell);
	else if (is_parent(pid))
		return (parent_proc(pid));
	else
		printf(RED "fork error\n" END);
	return (OK);
}
