#include "minishell.h"

t_fd	api_open(char *file, int flag)
{
	t_fd	fd;

	fd = open(file, flag, 0644);
	if (fd == ERR)
		return (error_syscall(file));
	else
		return (fd);
}

//	shell_heredoc sets exitcode through env->exitcode
t_fd	api_open_redirect_input(t_AST_NODE *redirect, t_shell *shell)
{
	char	*file;

	file = redirect->text;
	if (redirect->op == REDIR_HEREDOC)
		return (shell_heredoc(shell, file));
	else if (redirect->op == REDIR_INPUT)
		return (api_open(file, O_RDONLY));
	else
		return (error_msg_category("redirects", "unsupported type"));
}

t_res	api_open_redirect_output(t_AST_NODE *redirect)
{
	int		flag;
	char	*file;

	file = redirect->text;
	if (redirect->op == REDIR_OUTPUT)
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redirect->op == REDIR_OUTPUT_APPEND)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	else
		return (error_msg_category("redirects", "unsupported type"));
	return (api_open(file, flag));
}
