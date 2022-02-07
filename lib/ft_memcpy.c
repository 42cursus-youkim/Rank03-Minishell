/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:56:33 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 21:59:51 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*by_dst;
	unsigned char	*by_src;

	if (!dst && !src)
		return (0);
	by_dst = (unsigned char *)dst;
	by_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(by_dst + i) = *(by_src + i);
		i++;
	}
	return (dst);
}
