/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 19:17:03 by hyojekim          #+#    #+#             */
/*   Updated: 2021/06/03 20:58:43 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_find_newline(char *s)
{
	while (s != NULL && *s != '\0')
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (0);
}

static int	ft_split_line(char **line, char **file_box, int pos_newline)
{
	char	*temp;

	*line = (char *)malloc(sizeof(char) * pos_newline + 1);
	if (*line == NULL)
		return (-1);
	ft_strlcpy(*line, *file_box, pos_newline + 1);
	temp = ft_strdup(*file_box + pos_newline + 1);
	if (temp == NULL)
		return (-1);
	free(*file_box);
	*file_box = temp;
	return (1);
}

static int	ft_last_line(char **line, char **file_box, ssize_t num_read)
{
	if (num_read < 0)
		return (-1);
	if (*file_box == NULL)
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
		return (0);
	}
	*line = *file_box;
	*file_box = 0;
	return (0);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*rst;
	size_t	len;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (len + 1));
	if (rst == NULL)
		return (0);
	ft_strlcpy(rst, s1, len + 1);
	free(s1);
	ft_strlcat(rst, s2, len + 1);
	return (rst);
}

int	get_next_line(int fd, char **line)
{
	static char		*file_box[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	char			*pin;
	ssize_t			num_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	pin = ft_find_newline(file_box[fd]);
	while (pin == NULL)
	{
		num_read = read(fd, buf, BUFFER_SIZE);
		if (num_read > 0)
		{
			buf[num_read] = '\0';
			file_box[fd] = ft_strjoin_gnl(file_box[fd], buf);
			if (file_box[fd] == NULL)
				return (-1);
			pin = ft_find_newline(file_box[fd]);
		}
		else
			return (ft_last_line(line, &file_box[fd], num_read));
	}
	return (ft_split_line(line, &file_box[fd], pin - file_box[fd]));
}
