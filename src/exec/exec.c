#include "minishell.h"

void	child_proc_exec(t_AST_COMMAND *cmd, t_shell *shell)
{
	char			**argv;
	char			**envp;
	char			*executable;

	executable = new_executable_from_env(cmd->name->text, shell->env);
	argv = new_argv_from_cmd(executable, cmd);
	envp = new_env_to_envp(shell->env);
	if (execve(executable, argv, envp) == OK)
		return ;
	del_arr(envp);
	del_arr(argv);
	free(executable);
	api_exit(shell, EXIT_FAILURE);
}

static void	child_proc(t_shell *shell, int index)
{
	t_AST_COMMAND	*cmd;
	char			*text;

	cmd = shell->script->commands[index];
	text = cmd->name->text;
	printf(HYEL "HAYO I'm child\n" END);
	if (is_builtin(text))
	{
		// builtins_exec()
		printf(BRED "%s is builtin, please wait for a bit "
			"till it's implemented\n" END, text);
		api_exit(shell, EXIT_FAILURE);
	}
	if (is_executable_exists(text, shell->env))
		return ((void)child_proc_exec(cmd, shell));
	else
	{
		printf("cannot find executable %s\n", text);
		api_exit(shell, EXIT_FAILURE);
	}
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

int	api_exec_cmd_at(t_shell *shell, int index)
{
	pid_t	pid;

	pid = fork();
	if (is_child(pid))
		child_proc(shell, index);
	else if (is_parent(pid))
		return (parent_proc(pid));
	else
		printf(RED "fork error\n" END);
	return (OK);
}
