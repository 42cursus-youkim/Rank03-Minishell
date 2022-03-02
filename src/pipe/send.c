/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	api_send_output_to_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_READ]);
	api_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close(pipefd[PIPE_WRITE]);
}

void	api_receive_input_from_pipe(t_fd pipefd[PIPE_SIZE])
{
	close(pipefd[PIPE_WRITE]);
	api_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close(pipefd[PIPE_READ]);
}
