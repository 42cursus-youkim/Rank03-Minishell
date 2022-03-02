/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	api_open_redirect_input(
	t_fd *fd_p, t_AST_NODE *redirect, t_shell *shell)
{
	char	*file;

	if (is_fd_open(*fd_p))
		close(*fd_p);
	file = redirect->text;
	if (redirect->op == REDIR_HEREDOC)
		*fd_p = shell_heredoc(shell, file);
	else if (redirect->op == REDIR_INPUT)
		*fd_p = api_open(file, O_RDONLY);
	else
		*fd_p = error_msg_category("redirects", "unsupported type");
}

void	api_open_redirect_output(
	t_fd *fd_p, t_AST_NODE *redirect)
{
	int		flag;
	char	*file;

	if (is_fd_open(*fd_p))
		close(*fd_p);
	file = redirect->text;
	if (redirect->op == REDIR_OUTPUT)
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redirect->op == REDIR_OUTPUT_APPEND)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	else
	{
		*fd_p = error_msg_category("redirects", "unsupported type");
		return ;
	}
	*fd_p = api_open(file, flag);
}
