#include "minishell.h"

/*	does not use fork
	builtin_exit works differently inside pipe;
	since it won't close process
*/
int	builtin_run(t_AST_COMMAND *cmd, t_shell *shell)
{
	int						exitcode;
	t_context				context;
	const t_builtin			builtin = which_builtin(cmd->name->text);
	const t_builtinfunc_f	funcs[] = {
		builtin_echo,
		builtin_cd,
		builtin_pwd,
		builtin_export,
		builtin_unset,
		builtin_env,
		builtin_exit,
	};

	context_init(&context, cmd, shell->env);
	exitcode = funcs[builtin](&context, shell);
	env_set_exitcode(shell->env, exitcode);
	del_context(&context);
	return (shell->env->exitcode);
}
