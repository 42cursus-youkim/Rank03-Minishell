/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_scan2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metachar_attachable(char **pstr, char prev_c, char c)
{
	if (prev_c != '|' && ft_strlen(*pstr) == 1 && c == prev_c)
	{
		ft_str_append(pstr, c);
		return (true);
	}
	return (false);
}

bool	is_prev_metachar_attachable(char *str)
{
	return (is_str_equal(str, "") || is_str_equal(str, "|"));
}
