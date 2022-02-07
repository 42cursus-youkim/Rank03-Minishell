/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:19:09 by hyojekim          #+#    #+#             */
/*   Updated: 2021/07/19 15:49:15 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_array(char **rst, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
	{
		free(rst[i]);
		i++;
	}
	free(rst);
}

static int	count_word(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
		if (*s)
			s++;
	}
	return (cnt);
}

static int	split_word(char **rst, char const *s, char c)
{
	char	*pin;
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			pin = (char *)s;
			while (*s && *s != c)
				s++;
			rst[i] = (char *)malloc(sizeof(char) * (s - pin) + 1);
			if (rst[i] == NULL)
			{
				free_array(rst, i);
				return (0);
			}
			ft_strlcpy(rst[i], pin, s - pin + 1);
			i++;
		}
		if (*s)
			s++;
	}
	rst[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**rst;

	if (s == NULL)
		return (0);
	rst = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (rst == NULL)
		return (0);
	if (!split_word(rst, s, c))
		return (0);
	return (rst);
}
