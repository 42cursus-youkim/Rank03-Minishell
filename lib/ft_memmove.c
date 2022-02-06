/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:57:26 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 22:44:12 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*by_dst;
	unsigned char	*by_src;

	if (!dst && !src)
		return (0);
	by_dst = (unsigned char *)dst;
	by_src = (unsigned char *)src;
	if (dst <= src)
	{
		i = -1;
		while (++i < len)
			*(by_dst + i) = *(by_src + i);
	}
	else
	{
		i = len;
		while (i)
		{
			*(by_dst + i - 1) = *(by_src + i - 1);
			i--;
		}
	}
	return (dst);
}
