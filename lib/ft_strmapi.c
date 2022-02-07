/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 00:20:50 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 00:32:57 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rst;
	unsigned int	i;

	if (s == NULL)
		return (0);
	rst = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (rst == NULL)
		return (0);
	i = 0;
	while (*s != '\0')
	{
		rst[i] = f(i, *s++);
		i++;
	}
	rst[i] = '\0';
	return (rst);
}
