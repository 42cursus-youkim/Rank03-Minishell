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

bool	is_alpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_overflow(int n, int sign)
{
	return (
		(sign == -1 && n > 0)
		|| (sign == 1 && n < 0));
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}
