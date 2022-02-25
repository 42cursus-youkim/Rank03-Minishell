#include "minishell.h"

void	context_init(t_context *context, t_AST_COMMAND *cmd, t_dict *env)
{
	// cmd_connect_redeirects(cmd);
	context->executable = new_executable_from_env(cmd->name->text, env);
	context->argv = new_argv_from_cmd(context->executable, cmd);
	context->envp = new_env_to_envp(env);
}

void	cmd_connect_redirects(t_AST_COMMAND *cmd)
{
	if (cmd->io_input != UNSET)
		dup2(cmd->io_input, STDIN_FILENO);
	if (cmd->io_output != UNSET)
		dup2(cmd->io_output, STDOUT_FILENO);
}

void	del_context(t_context *context)
{
	del_arr(context->envp);
	del_arr(context->argv);
	free(context->executable);
}
