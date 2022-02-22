#include "minishell.h"

int	ast_nodes_len(t_AST_NODE *nodes[])
{
	int	i;

	i = 0;
	while (nodes[i])
		i++;
	return (i);
}

char	**new_argv_from_cmd(char *executable, t_AST_COMMAND *cmd)
{
	int			i;
	char		**argv;
	const int	len = ast_nodes_len(cmd->suffixes);

	argv = ft_calloc(sizeof(char *), len + 1);
	if (!argv)
		return (NULL);
	argv[0] = new_str(executable);
	i = -1;
	while (++i < len)
	{
		argv[i + 1] = new_str(cmd->suffixes[i]->text);
	}
	return (argv);
}

void	child_proc_exec(t_AST_SCRIPTS *scripts, t_shell *shell)
{
	t_AST_COMMAND	*cmd;
	char			**argv;
	char			**envp;
	char			*executable;

	cmd = scripts->commands[0];
	executable = new_executable_from_env(cmd->name->text, shell->env);
	argv = new_argv_from_cmd(executable, cmd);
	envp = new_env_to_envp(shell->env);
	if (execve(executable, argv, envp) == OK)
		return ;
	del_arr(envp);
	del_arr(argv);
	free(executable);
	api_exit(shell, scripts, EXIT_FAILURE);
}

static void	child_proc(t_AST_SCRIPTS *scripts, t_shell *shell)
{
	t_AST_COMMAND	*cmd;
	char			*text;

	cmd = scripts->commands[0];
	text = cmd->name->text;
	printf(HYEL "HAYO I'm child\n" END);
	if (is_builtin(text))
	{
		// builtins_exec()
		printf(BRED "%s is builtin, please wait for a bit "
			"till it's implemented\n" END, text);
		api_exit(shell, scripts, EXIT_FAILURE);
	}
	if (is_executable_exists(text, shell->env))
		return ((void)child_proc_exec(scripts, shell));
	else
	{
		printf("cannot find executable %s\n", text);
		api_exit(shell, scripts, EXIT_FAILURE);
	}
}

static int	parent_proc(pid_t pid, t_shell *shell)
{
	int	status;

	printf(HGRN "HAYO I'm Parent process\n" END);
	waitpid(pid, &status, 0);
	shell->exitcode = api_handle_status(status);
	if (shell->exitcode == OK)
	{
		printf(BGRN "HAYO child is successfully dead!\n" END);
		return (OK);
	}
	else
	{
		printf(BRED "exitcode: %d\n" END, shell->exitcode);
		return (shell->exitcode);
	}
}

int	api_exec_cmd(t_AST_SCRIPTS *scripts, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (is_child(pid))
		child_proc(scripts, shell);
	else if (is_parent(pid))
		return (parent_proc(pid, shell));
	else
		printf(RED "fork error\n" END);
	return (OK);
}
