#include "minishell.h"

bool	is_redirect_input(t_redirect_op op)
{
	return (op == REDIR_INPUT || op == REDIR_HEREDOC);
}

bool	is_redirect_output(t_redirect_op op)
{
	return (op == REDIR_OUTPUT || op == REDIR_OUTPUT_APPEND);
}
