/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_quotechar(char c)
{
	if (c == '\"' || c == '\'')
		return (true);
	return (false);
}

bool	is_tilde_expansion(t_scan_data *data, int i)
{
	if (data->line[i] == '~'
		&& is_str_equal(data->buf, "")
		&& !is_quotes_open(NULL, data->buf, QUOTE_CLOSE, '\0')
		&& (!data->line[i + 1] || data->line[i + 1] == ' '
			|| data->line[i + 1] == '/'))
		return (true);
	return (false);
}
