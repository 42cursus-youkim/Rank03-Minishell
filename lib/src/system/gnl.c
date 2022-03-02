/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sliced(char **backup_str_p, int nl_idx, bool *is_finish)
{
	char	*sliced_str;

	sliced_str = new_str_slice(*backup_str_p,
			0,
			nl_idx + 1);
	ft_str_replace(backup_str_p,
		new_str_slice(*backup_str_p,
			nl_idx + 1,
			ft_strlen(*backup_str_p)));
	if (ft_strlen(*backup_str_p) == 0)
	{
		free(*backup_str_p);
		*is_finish = true;
	}
	return (sliced_str);
}

static char	*result(char **backup_str_p, int read_length, bool *is_finish)
{
	char	*temp;

	if (read_length == ERR || ft_strlen(*backup_str_p) == 0)
		return (NULL);
	temp = new_str(*backup_str_p);
	free(*backup_str_p);
	*is_finish = true;
	*backup_str_p = NULL;
	return (temp);
}

/*	returns NULL if no line to read. does not keep '\n'.
	it uses static char*[] to hold the lines.
*/
char	*ft_gnl(int fd)
{
	int			nl_idx;
	int			read_length;
	char		buf[BUFFER_SIZE + 1];
	static bool	is_finished[OPEN_MAX];
	static char	*backup[OPEN_MAX];

	if (is_finished[fd])
		return (NULL);
	if (!backup[fd])
		backup[fd] = new_str("");
	read_length = 0;
	while (true)
	{
		read_length = ft_read(fd, buf, BUFFER_SIZE);
		if (read_length == 0)
			break ;
		else if (read_length == ERR)
			return (NULL);
		ft_str_extend(&backup[fd], buf);
		nl_idx = ft_strchr_i(backup[fd], '\n');
		if (nl_idx >= 0)
			return (sliced(&backup[fd], nl_idx, &is_finished[fd]));
	}
	return (result(&backup[fd], read_length, &is_finished[fd]));
}
