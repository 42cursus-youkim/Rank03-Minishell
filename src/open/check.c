/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 17:41:18 by youkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	is_relative_path(char *path)
{
	return (is_path(path)
		&& ft_strlen(path) >= 2
		&& path[0] == '.'
		&& path[1] == '/');
}
