/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_1stchar_valid(char c)
{
	if (is_alpha(c) || c == '_' || c == '{' || c == '?')
		return (true);
	return (false);
}

bool	is_variable_char_valid(char c)
{
	if (is_alpha(c) || is_digit(c) || c == '_')
		return (true);
	return (false);
}

bool	is_scan_continuos(char *buf, char c, t_scanner_type type)
{
	if (!c || (type == CMD
			&& (!is_quotes_open(NULL, buf, QUOTE_CLOSE, '\0')
				&& !is_brace_open(buf)
				&& (is_whitespace(c) || is_metachar(c)))))
		return (false);
	return (true);
}

t_res	free_n_return(void *data, t_res result)
{
	free(data);
	return (result);
}

t_res	free_arr_n_return(char *arr[], t_res result)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	return (result);
}
