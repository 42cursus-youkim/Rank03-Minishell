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

t_res	api_create_pipe(t_fd pipefd[PIPE_SIZE])
{
	t_res	res;

	res = pipe(pipefd);
	if (res == ERR)
		return (error_syscall("pipe"));
	return (res);
}

void	api_copy_pipe(t_fd from[PIPE_SIZE], t_fd to[PIPE_SIZE])
{
	to[PIPE_READ] = from[PIPE_READ];
	to[PIPE_WRITE] = from[PIPE_WRITE];
}

void	api_close_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
}

int	wait_pipe_processes(int pids[], const int len)
{
	int	i;
	int	status;

	i = -1;
	while (++i < len)
		waitpid(pids[i], &status, 0);
	return (status);
}
