/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	context_init(t_context *context, t_AST_COMMAND *cmd, t_dict *env)
{
	cmd_connect_redirects(cmd);
	context->executable = new_executable_from_env(cmd->name->text, env);
	context->argv = new_argv_from_cmd(context->executable, cmd);
	context->envp = new_env_to_envp(env);
}

void	cmd_connect_redirects(t_AST_COMMAND *cmd)
{
	if (is_fd_open(cmd->io[INPUT]))
	{
		api_dup2(cmd->io[INPUT], STDIN_FILENO);
		close(cmd->io[INPUT]);
	}
	if (is_fd_open(cmd->io[OUTPUT]))
	{
		api_dup2(cmd->io[OUTPUT], STDOUT_FILENO);
		close(cmd->io[OUTPUT]);
	}
}

void	del_context(t_context *context)
{
	del_arr(context->envp);
	del_arr(context->argv);
	free(context->executable);
}
