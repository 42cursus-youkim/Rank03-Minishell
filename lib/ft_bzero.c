/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:43:21 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/20 11:47:01 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*by_s;

	i = 0;
	by_s = (unsigned char *)s;
	while (i < n)
	{
		*(by_s + i) = 0;
		i++;
	}
}
