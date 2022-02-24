#include "minishell.h"

void	child_proc_exec(t_AST_COMMAND *cmd, t_shell *shell)
{
	t_context	context;

	context_init(&context, cmd, shell->env);
	if (execve(context.executable, context.argv, context.envp) == OK)
		return (OK);
	del_context(&context);
	api_exit(shell, EXIT_FAILURE);
}

static void	child_proc(t_shell *shell, int index)
{
	t_AST_COMMAND	*cmd;
	char			*text;

	cmd = shell->script->commands[index];
	text = cmd->name->text;
	if (is_builtin(text))
		return ((void)builtins_exec(cmd, shell));
	if (is_executable_exists(text, shell->env))
		return ((void)child_proc_exec(cmd, shell));
	else
	{
		printf("cannot find executable %s\n", text);
		api_exit(shell, EXIT_FAILURE);
	}
}

static int	parent_proc(pid_t pid, t_dict *env)
{
	int	status;
	int	exitcode;

	waitpid(pid, &status, 0);
	exitcode = api_handle_status(status);
	env_set_exitcode(env, exitcode);
	if (exitcode == OK)
	{
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
		return (parent_proc(pid, shell->env));
	else
		printf(RED "fork error\n" END);
	return (OK);
}
