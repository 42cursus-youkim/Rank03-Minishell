#include "minishell.h"

static int	TODO(t_context *context, t_shell *shell)
{
	(void)context;
	(void)shell;
	printf(BBLU "TODO\n" END);
	return (EXIT_BUILTINS_ERR);
}


//	does not use fork
int	builtin_run(t_AST_COMMAND *cmd, t_shell *shell)
{
	int						exitcode;
	t_context				context;
	const t_builtin			builtin = which_builtin(cmd->name->text);
	const t_builtinfunc_f	funcs[] = {
		builtin_echo,
		builtin_cd,
		builtin_pwd,
		TODO, // builtin_export,
		TODO, // builtin_unset,
		builtin_env,
		TODO, // builtin_exit
	};

	if (builtin == BUILTIN_EXIT)
		api_exit(shell, EXIT_SUCCESS);
	context_init(&context, cmd, shell->env);
	exitcode = funcs[builtin](&context, shell);
	env_set_exitcode(shell->env, exitcode);
	del_context(&context);
	return (shell->env->exitcode);
	// api_exit(shell, EXIT_SUCCESS);
}
