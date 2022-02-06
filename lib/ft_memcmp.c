/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:18:07 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 22:47:00 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*by_s1;
	unsigned char	*by_s2;

	if (n == 0)
		return (0);
	by_s1 = (unsigned char *)s1;
	by_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*(by_s1 + i) != *(by_s2 + i))
			return ((int)(*(by_s1 + i) - *(by_s2 + i)));
		i++;
	}
	return (0);
}
