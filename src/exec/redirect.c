#include "minishell.h"

static void	redirect_output(t_AST_NODE *redirect)
{
	int		fd;

	if (api_open(&fd, redirect) == ERR)
		return ;
	dup2(fd, STDOUT_FILENO);
}

static void	redirect_input(t_AST_NODE *redirect)
{
	int		fd;

	if (api_open(&fd, redirect) == ERR)
		return ;
	dup2(STDIN_FILENO, fd);
}

void	api_create_redirect(t_AST_NODE *redirect)
{
	const t_redirect_op	op = redirect->op;

	if (op == NOT_REDIR)
		return ;
	else if (op == REDIR_OUTPUT || op == REDIR_OUTPUT_APPEND)
		redirect_output(redirect);
	else if (op == REDIR_INPUT)
		redirect_input(redirect);
	else if (op == REDIR_HEREDOC || op == REDIR_HEREDOC_UNSET)
		printf(RED "Not implemented" END);
}
