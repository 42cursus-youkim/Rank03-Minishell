#include "minishell.h"

static t_res	api_open_inner(char *file, int flag)
{
	t_fd	fd;

	fd = open(file, flag, 0644);
	if (fd == ERR)
		return (error_syscall(file));
	else
		return (fd);
}

/*	currently:
	REDIR_INPUT = 0,
	REDIR_HEREDOC = 1,
	REDIR_OUTPUT = 2,
	REDIR_OUTPUT_APPEND = 3,
	NOT_REDIR = -1,
*/
t_res	api_open(t_fd *fd_p, t_AST_NODE *redirect, t_shell *shell)
{
	char		*file;
	int			flag;
	const int	flags[5] = {
		O_RDONLY,
		OK,
		O_CREAT | O_WRONLY | O_TRUNC,
		O_CREAT | O_WRONLY | O_APPEND,
		ERR};

	file = redirect->text;
	flag = flags[redirect->op];
	if (flag == ERR)
		return (ERR);
	if (*fd_p > STDERR_FILENO)
		close(*fd_p);
	if (redirect->op == REDIR_HEREDOC)
		*fd_p = shell_heredoc(shell, file);
	else
		*fd_p = api_open_inner(file, flag);
	if (*fd_p == ERR)
		return (ERR);
	return (OK);
}
