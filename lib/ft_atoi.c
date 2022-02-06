/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:40:51 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/08 15:03:06 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			sign;
	long long	rst;
	long long	temp;

	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n'
		|| *str == '\v' || *str == '\f')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	rst = 0;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		temp = rst * 10 + *str++ - '0';
		if (temp < rst)
		{
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		rst = temp;
	}
	return (sign * (int)rst);
}
