#include "minishell.h"

void	context_init(t_context *context, t_AST_COMMAND *cmd, t_dict *env)
{
	context->executable = new_executable_from_env(cmd->name->text, env);
	context->argv = new_argv_from_cmd(context->executable, cmd);
	context->envp = new_env_to_envp(env);
}

//	Always return ERR
t_res	context_run_and_free(t_context *context)
{
	if (execve(context->executable, context->argv, context->envp) == OK)
		return (OK);
	del_arr(context->envp);
	del_arr(context->argv);
	free(context->executable);
	return (ERR);
}
