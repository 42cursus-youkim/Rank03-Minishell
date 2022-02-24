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

//	TODO: move functions below to suitable place?
/*	Opens fd, save to cmd and create file if needed
	does NOT connect fd to STDIN/STDOUT,
	that's done on command execution
*/
void	cmd_open_redirect(t_AST_COMMAND *cmd, t_shell *shell)
{
	int			i;
	t_AST_NODE	*node;
	const int	suffix_len = ast_nodes_len(cmd->suffixes);

	// const int	prefix_len = ast_nodes_len(cmd->prefixes);

	// i = -1;
	// while (++i < prefix_len)
	// 	api_open(&cmd->io_input, cmd->prefixes[i]->text);
	i = -1;
	while (++i < suffix_len)
	{
		node = cmd->suffixes[i];
		if (node->type == REDIRECT)
		{
			if (node->op == REDIR_HEREDOC)
			{
				if (cmd->io_output > STDERR_FILENO)
					close(cmd->io_output);
				cmd->io_output = shell_heredoc(shell, node->text);
			}
			else
				api_open(&cmd->io_output, node);
		}
	}
}

void	shell_open_redirects(t_shell *shell)
{
	int			i;
	const int	len = shell->script->commands_len;

	i = -1;
	while (++i < len)
		cmd_open_redirect(
			shell->script->commands[i], shell);
}
