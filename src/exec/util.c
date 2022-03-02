/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_parent(pid_t pid)
{
	return (pid > 0);
}

bool	is_child(pid_t pid)
{
	return (pid == 0);
}

bool	is_fd_open(t_fd fd)
{
	return (fd > STDERR_FILENO);
}

//	same with dup2 but with error handling
t_fd	api_dup2(t_fd from, t_fd to)
{
	int	res;

	res = dup2(from, to);
	if (res == ERR)
		error_syscall("dup2");
	return (res);
}

t_fd	api_dup(t_fd from)
{
	int	res;

	res = dup(from);
	if (res == ERR)
		error_syscall("dup");
	return (res);
}
