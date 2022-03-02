/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_str_first(char *str, char c)
{
	if (!str || ft_strlen(str) < 1)
		return (false);
	return (str[0] == c);
}

bool	is_str_last(char *str, char c)
{
	if (!str || ft_strlen(str) < 1)
		return (false);
	return (str[ft_strlen(str) - 1] == c);
}

bool	is_str_digit(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = -1;
	while (str[++i])
		if (!is_digit(str[i]))
			return (false);
	return (true);
}
