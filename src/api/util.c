/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:19:39 by youkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	frees allocated memory from shell && exits with exitcode
void	api_exit(t_shell *shell, int exitcode)
{
	del_shell(shell);
	exit(exitcode);
}

void	api_show_logo(char *file)
{
	t_fd	fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == ERR)
		return ;
	while (true)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		printf(BBLU "%s" END, line);
		free(line);
	}
}
