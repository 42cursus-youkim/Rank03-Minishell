/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:58:56 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/10 21:35:07 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trimset(char const *set, char c)
{
	if (ft_strchr(set, c) != NULL)
		return (1);
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	len;

	if (s1 == NULL)
		return (0);
	while (is_trimset(set, *s1) && *s1 != '\0')
		s1++;
	len = ft_strlen(s1);
	if (len > 0)
		while (is_trimset(set, s1[len - 1]))
			len--;
	s2 = (char *)malloc(sizeof(char) * len + 1);
	if (s2 == NULL)
		return (0);
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}
