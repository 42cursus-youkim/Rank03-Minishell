/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_executable_exists(char *file, t_dict *env)
{
	int		i;
	char	**names;
	bool	result;

	if (is_path(file))
		return (true);
	names = new_names_from_path(file, env);
	i = -1;
	result = false;
	while (names[++i])
		if (is_path(names[i]))
			result = true;
	del_arr(names);
	return (result);
}

/*	only time it would fail to get executable is when
	the command is builtin, hence returns empty string
*/
char	*new_executable_from_env(char *file, t_dict *env)
{
	int		i;
	char	**path;
	char	*executable;

	if (is_absolute_path(file) && !is_dir(file))
		return (new_str(file));
	else if (!is_executable_exists(file, env))
		return (new_str(""));
	path = new_names_from_path(file, env);
	i = -1;
	while (path[++i])
		if (is_path(path[i]))
			break ;
	executable = new_str(path[i]);
	del_arr(path);
	return (executable);
}
