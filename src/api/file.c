#include "minishell.h"

/*	currently:
	REDIR_INPUT = 0,
	REDIR_HEREDOC = 1,
	REDIR_OUTPUT = 2,
	REDIR_OUTPUT_APPEND = 3,
	REDIR_HEREDOC_UNSET = -2,
	NOT_REDIR = -1,
*/
t_res	api_open(t_fd *fd_p, t_AST_NODE *redirect)
{
	const char	*file = redirect->text;
	int			flag;
	const int	flags[6] = {
		O_RDONLY,
		ERR,
		O_CREAT | O_WRONLY | O_TRUNC,
		O_CREAT | O_WRONLY | O_APPEND,
		ERR,
		ERR};

	flag = flags[redirect->op];
	if (flag == ERR)
		return (ERR);
	*fd_p = open(file, flag, 0644);
	if (*fd_p == ERR)
		return (ERR);
	return (OK);
}
