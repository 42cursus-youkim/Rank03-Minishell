/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	similar to read but NULL-terminates the string. returns sizes read.
	string size should be at least 1 bigger than the buffer_size.
*/
int	ft_read(int fd, char *buf, int buffer_size)
{
	int	len;

	ft_bzero(buf, buffer_size + 1);
	len = read(fd, buf, buffer_size);
	return (len);
}
