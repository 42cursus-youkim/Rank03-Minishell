/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:04:41 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/20 11:41:38 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*by_dst;
	unsigned char	*by_src;
	unsigned char	by_c;

	by_dst = (unsigned char *)dst;
	by_src = (unsigned char *)src;
	by_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*(by_dst + i) = *(by_src + i);
		if (*(by_src + i) == by_c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
