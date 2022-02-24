#include "minishell.h"
// static void	redirect_output(t_AST_NODE *redirect)
// {
// 	int		fd;

// 	if (api_open(&fd, redirect) == ERR)
// 		return ;
// 	dup2(fd, STDOUT_FILENO);
// }

// static void	redirect_input(t_AST_NODE *redirect)
// {
// 	int		fd;

// 	if (api_open(&fd, redirect) == ERR)
// 		return ;
// 	dup2(STDIN_FILENO, fd);
// }

// void	api_create_redirect(t_AST_NODE *redirect)
// {
// 	const t_redirect_op	op = redirect->op;

// 	if (op == NOT_REDIR)
// 		return ;
// 	else if (op == REDIR_OUTPUT || op == REDIR_OUTPUT_APPEND)
// 		redirect_output(redirect);
// 	else if (op == REDIR_INPUT)
// 		redirect_input(redirect);
// 	else if (op == REDIR_HEREDOC || op == REDIR_HEREDOC_UNSET)
// 		printf(RED "Not implemented" END);
// }

// void	api_open_redirect(t_AST_NODE *node, t_AST_COMMAND *cmd)
// {

// }

/*	currently:
	REDIR_INPUT = 0,
	REDIR_HEREDOC = 1,
	REDIR_OUTPUT = 2,
	REDIR_OUTPUT_APPEND = 3,
	NOT_REDIR = -1,
*/
t_res	api_open(t_fd *fd_p, t_AST_NODE *redirect)
{
	const char	*file = redirect->text;
	int			flag;
	const int	flags[5] = {
		O_RDONLY,
		ERR,
		O_CREAT | O_WRONLY | O_TRUNC,
		O_CREAT | O_WRONLY | O_APPEND,
		ERR};

	flag = flags[redirect->op];
	if (flag == ERR)
		return (ERR);
	if (*fd_p > STDERR_FILENO)
		close(*fd_p);
	*fd_p = open(file, flag, 0644);
	if (*fd_p == ERR)
		return (ERR);
	return (OK);
}

//	TODO: refactor later, this is very dirty
void	cmd_try_open_redirect(
	t_AST_NODE *node, t_AST_COMMAND *cmd, t_shell *shell)
{
	t_fd	*fd_p;

	if (node->type != REDIRECT)
		return ;
	if (node->op == REDIR_HEREDOC || node->op == REDIR_INPUT)
		fd_p = &cmd->io_input;
	else if (node->op == REDIR_OUTPUT || node->op == REDIR_OUTPUT_APPEND)
		fd_p = &cmd->io_output;
	else
		return ;
	// printf("[redirect] %s\n", node->text);
	if (node->op == REDIR_HEREDOC)
	{
		if (*fd_p > STDERR_FILENO)
			close(*fd_p);
		*fd_p = shell_heredoc(shell, node->text);
	}
	else
		api_open(fd_p, node);
}

//	TODO: move functions below to suitable place?
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
