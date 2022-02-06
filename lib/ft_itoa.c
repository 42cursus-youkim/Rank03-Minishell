/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:41:26 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/20 11:49:28 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_size(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	num_abs(int x)
{
	if (x < 0)
		return (-1 * x);
	else
		return (x);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*rst;

	len = num_size(n);
	sign = 0;
	rst = (char *)malloc(sizeof(char) * len + 1);
	if (rst == NULL)
		return (0);
	if (n < 0)
	{
		rst[0] = '-';
		sign = 1;
	}
	rst[len] = '\0';
	while (len - sign > 0)
	{
		rst[len - 1] = num_abs(n % 10) + '0';
		n /= 10;
		len--;
	}
	return (rst);
}
