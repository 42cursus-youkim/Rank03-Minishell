/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:38:05 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/08 14:26:00 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	int2char_fd(int n, int fd)
{
	char	c;

	if (n < 0)
		c = n * (-1) + '0';
	else
		c = n + '0';
	write(fd, &c, 1);
}

static void	recur_nbr_fd(int n, int fd)
{
	if (n / 10 != 0)
	{
		recur_nbr_fd(n / 10, fd);
		int2char_fd(n % 10, fd);
	}
	else
		int2char_fd(n, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n < 0)
		write(fd, "-", 1);
	recur_nbr_fd(n, fd);
}
