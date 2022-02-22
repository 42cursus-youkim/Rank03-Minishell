#include "minishell.h"


// char	**new_api_resolved_argv(t_AST_COMMAND *cmd, t_dict *env)
// {
// 	char	**argv;

// 	names = n

// 	argv = new_arr(NULL);
// }

// /* FIXME:
// 	char *argv[]
// 	-> t_AST_COMMAND *cmd, t_dict *env
// */
// void	api_raw_exec(t_AST_COMMAND *cmd, t_dict *env)
// {
// 	char	**argv;
// 	(void)env;

// 	printf(HYEL "HAYO I'm child\n" END);
// 	argv = new_api_resolved_argv(cmd, env);
// 	char *envp[] = {NULL};
// 	if (execve(argv[0], argv, envp) == OK)
// 		exit(0);
// 	printf(RED "Execve fail!\n" END);
// 	exit(1);
// }


static void	child_proc(t_AST_PIPELINE *pipeline, t_shell *shell)
{
	t_AST_COMMAND	*cmd;
	char			*name;
	char			**names;

	printf(HYEL "HAYO I'm child\n" END);
	cmd = pipeline->commands[0];
	name = cmd->name->text;
	names = new_path_with_name(name, shell->env);
	ft_arr_print(names);
	del_arr(names);
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

int	api_exec_cmd(t_AST_PIPELINE *pipeline, t_shell *shell)
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
