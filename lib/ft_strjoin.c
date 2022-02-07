/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:45:19 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/11 00:18:13 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (len + 1));
	if (rst == NULL)
		return (0);
	ft_strlcpy(rst, s1, len + 1);
	ft_strlcat(rst, s2, len + 1);
	return (rst);
}
