#include "minishell.h"

//	Used by child_proc
void	builtins_exec(t_AST_COMMAND *cmd, t_shell *shell)
{
	t_context		context;
	const t_builtin	builtin = which_builtin(cmd->name->text);

	context_init(&context, cmd, shell->env);
	// if (builtin == ERR)
	// 	api_exit(shell, EXIT_FAILURE);
	if (builtin == BUILTIN_ECHO)
		builtin_echo(&context);
	else if (builtin == BUILTIN_PWD)
		builtin_pwd(shell->env);
	// else if (builtin == BUILTIN_CD)
	else if (builtin == BUILTIN_ENV)
		env_print(shell->env);
	del_context(&context);
	api_exit(shell, EXIT_SUCCESS);
}
