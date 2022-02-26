#include "minishell.h"

static void	TODO(t_context *context, t_shell *shell)
{
	(void)context;
	(void)shell;
	printf(BBLU "TODO\n" END);
}

//	Used by child_proc
void	builtins_exec(t_AST_COMMAND *cmd, t_shell *shell)
{
	t_context				context;
	const t_builtin			builtin = which_builtin(cmd->name->text);
	const t_builtinfunc_f	funcs[] = {
		builtin_echo,
		TODO, // builtin_cd,
		builtin_pwd,
		TODO, // builtin_export,
		TODO, // builtin_unset,
		builtin_env,
		TODO, // builtin_exit
	};

	context_init(&context, cmd, shell->env);
	funcs[builtin](&context, shell);
	del_context(&context);
	api_exit(shell, EXIT_SUCCESS);
}
