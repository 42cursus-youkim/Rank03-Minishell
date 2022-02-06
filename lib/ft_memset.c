/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:14:18 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 17:50:54 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*by_b;
	unsigned char	by_c;

	by_b = (unsigned char *)b;
	by_c = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		*(by_b + i) = by_c;
		i++;
	}
	return (b);
}
