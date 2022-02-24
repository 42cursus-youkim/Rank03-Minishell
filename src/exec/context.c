#include "minishell.h"

void	context_init(t_context *context, t_AST_COMMAND *cmd, t_dict *env)
{
	context->executable = new_executable_from_env(cmd->name->text, env);
	context->argv = new_argv_from_cmd(context->executable, cmd);
	context->envp = new_env_to_envp(env);
}

void	del_context(t_context *context)
{
	del_arr(context->envp);
	del_arr(context->argv);
	free(context->executable);
}
