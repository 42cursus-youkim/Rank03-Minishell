/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:45:35 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/08 17:35:50 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dest;

	len = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (0);
	i = 0;
	while (*s1 != '\0')
		dest[i++] = *s1++;
	dest[i] = '\0';
	return (dest);
}
