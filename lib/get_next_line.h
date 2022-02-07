/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 19:17:58 by hyojekim          #+#    #+#             */
/*   Updated: 2021/06/03 20:58:07 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int		get_next_line(int fd, char **line);

#endif
