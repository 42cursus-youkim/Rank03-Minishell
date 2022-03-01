#include "minishell.h"

void	cmd_try_open_redirect(
	t_AST_NODE *node, t_AST_COMMAND *cmd, t_shell *shell)
{
	t_fd	*fd_p;

	if (node->type != REDIRECT)
		return ;
	if (node->op == REDIR_HEREDOC || node->op == REDIR_INPUT)
		fd_p = &cmd->io[INPUT];
	else if (node->op == REDIR_OUTPUT || node->op == REDIR_OUTPUT_APPEND)
		fd_p = &cmd->io[OUTPUT];
	else
		return ;
	api_open(fd_p, node, shell);
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
