/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:40:57 by hyojekim          #+#    #+#             */
/*   Updated: 2021/05/08 16:22:22 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			temp = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (temp);
}
