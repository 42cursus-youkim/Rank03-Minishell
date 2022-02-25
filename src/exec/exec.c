#include "minishell.h"

//	Used by child_proc
void	any_exec(t_AST_COMMAND *cmd, t_shell *shell)
{
	t_context	context;

	context_init(&context, cmd, shell->env);
	if (execve(context.executable, context.argv, context.envp) == OK)
		return ;
	del_context(&context);
	api_exit(shell, EXIT_FAILURE);
}

void	child_proc(t_shell *shell, int index)
{
	t_AST_COMMAND	*cmd;
	char			*text;

	cmd = shell->script->commands[index];
	text = cmd->name->text;
	if (is_builtin(text))
		return ((void)builtins_exec(cmd, shell));
	if (is_executable_exists(text, shell->env))
		return ((void)any_exec(cmd, shell));
	else
	{
		// error_msg_return((char *[]){BRED, MINISHELL, NULL})
		printf(RED "cannot find executable %s\n" END, text);
		api_exit(shell, EXIT_COMMAND_NOT_IN_PATH);
	}
}

//	save exitcode as string to env, also returns exitcode as int
int	api_handle_exitcode(t_dict *env, int status)
{
	const int	exitcode = api_handle_status(status);

	env_set_exitcode(env, exitcode);
	return (exitcode);
}

int	api_exec_cmd_at(t_shell *shell, int index)
{
	int	status;
	pid_t	pid;

	pid = fork();
	if (is_child(pid))
		child_proc(shell, index);
	else if (is_parent(pid))
	{
		waitpid(pid, &status, 0);
		return (api_handle_exitcode(shell->env, status));
	}
	else
		printf(RED "fork error\n" END);
	return (OK);
}
