/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:11:10 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 22:40:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*by_temp;
	unsigned char	by_c;

	by_temp = (unsigned char *)s;
	by_c = (unsigned char)c;
	while (n--)
	{
		if (*by_temp == by_c)
			return ((void *)by_temp);
		by_temp++;
	}
	return (0);
}
