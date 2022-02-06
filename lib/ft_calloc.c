/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:30:58 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 22:36:29 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*rst;
	size_t			i;

	rst = malloc(num * size);
	if (rst == NULL)
		return (0);
	i = 0;
	while (i < num * size)
	{
		*(rst + i) = 0;
		i++;
	}
	return ((void *)rst);
}
