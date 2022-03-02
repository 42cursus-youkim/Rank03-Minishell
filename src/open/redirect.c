/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 17:50:28 by youkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect_input(t_redirect_op op)
{
	return (op == REDIR_INPUT || op == REDIR_HEREDOC);
}

bool	is_redirect_output(t_redirect_op op)
{
	return (op == REDIR_OUTPUT || op == REDIR_OUTPUT_APPEND);
}

void	cmd_try_open_redirect(
	t_AST_NODE *redirect, t_AST_COMMAND *cmd, t_shell *shell)
{
	if (redirect->type != REDIRECT)
		return ;
	if (is_redirect_input(redirect->op))
		api_open_redirect_input(&cmd->io[INPUT], redirect, shell);
	else if (is_redirect_output(redirect->op))
		api_open_redirect_output(&cmd->io[OUTPUT], redirect);
	else
		return ;
	if (cmd->io[INPUT] == ERR || cmd->io[OUTPUT] == ERR)
	{
		cmd->is_fail = true;
		env_set_exitcode(shell->env, EXIT_FAILURE);
	}
}

/*	Opens fd, save to cmd and create file if needed
	does NOT connect fd to STDIN/STDOUT,
	that's done on command execution
*/
void	cmd_open_redirects(t_AST_COMMAND *cmd, t_shell *shell)
{
	int			i;
	const int	prefix_len = ast_nodes_len(cmd->prefixes);
	const int	suffix_len = ast_nodes_len(cmd->suffixes);

	i = -1;
	while (++i < prefix_len)
		cmd_try_open_redirect(
			cmd->prefixes[i], cmd, shell);
	i = -1;
	while (++i < suffix_len)
		cmd_try_open_redirect(
			cmd->suffixes[i], cmd, shell);
}

void	shell_open_redirects(t_shell *shell)
{
	int			i;
	const int	len = shell->script->commands_len;

	i = -1;
	while (++i < len)
		cmd_open_redirects(
			shell->script->commands[i], shell);
}
