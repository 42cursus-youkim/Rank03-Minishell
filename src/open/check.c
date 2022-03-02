/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect_input(t_redirect_op op)
{
	return (op == REDIR_INPUT || op == REDIR_HEREDOC);
}

bool	is_redirect_output(t_redirect_op op)
{
	return (op == REDIR_OUTPUT || op == REDIR_OUTPUT_APPEND);
}

bool	is_dir(char *path)
{
	struct stat	buffer;

	stat(path, &buffer);
	return (is_path(path) && S_ISDIR(buffer.st_mode));
}

bool	is_path(char *path)
{
	struct stat	buffer;

	return (stat(path, &buffer) == OK);
}

bool	is_absolute_path(char *path)
{
	return (is_path(path) && is_str_first(path, '/'));
}
