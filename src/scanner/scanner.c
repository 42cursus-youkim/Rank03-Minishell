/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_res	error_unclosed(char c, t_scan_data *data)
{
	char	*quote_str;

	quote_str = (char []){'(', c, ')', ':', ' ', '\0'};
	return (free_n_return(data->buf, error_with_exitcode((char *[]){
				QUOTE_ERROR, quote_str, MULTILINE_ERROR, NULL}, data->env, 2)));
}

static t_res	scan_last_check(t_list **scan_list, t_scan_data *data)
{
	char	last_quote;

	if (is_quotes_open(&last_quote, data->buf, QUOTE_CLOSE, '\0'))
		return (error_unclosed(last_quote, data));
	buf_to_list(scan_list, &data->buf);
	free(data->buf);
	return (OK);
}

static t_res	tilde_scan(t_scan_data *data)
{
	int			i;
	const int	len = ft_strlen(data->line);
	char		**split_arr;

	i = data->idx;
	if (!is_tilde_expansion(data, i))
		return (UNSET);
	split_arr = new_arr((char *[]){NULL});
	ft_arr_append_free(&split_arr, new_str_slice(data->line, 0, i));
	ft_arr_append(&split_arr, "$HOME");
	ft_arr_append_free(&split_arr, new_str_slice(data->line, i + 1, len));
	ft_str_replace(&data->line, new_str_join(split_arr, '\0'));
	del_arr(split_arr);
	data->idx = --i;
	return (OK);
}

static t_res	scanner_loop(t_list **scan_list, t_scan_data *data)
{
	t_res	scan_res;

	while (data->line[++(data->idx)])
	{
		if (whitespace_scan(scan_list, data) == OK)
			continue ;
		scan_res = dollar_scan(scan_list, data);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (ERR);
		scan_res = metachar_scan(scan_list, data);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (ERR);
		if (tilde_scan(data) == OK)
			continue ;
		ft_str_append(&data->buf, data->line[data->idx]);
	}
	return (scan_last_check(scan_list, data));
}

/*
	scan line and create scan_list
	- ERR: syntax error, unclosed error
*/
t_res	scanner(t_list **scan_list, char *line, t_dict *env)
{
	t_scan_data	data;

	data.line = new_str(line);
	data.idx = -1;
	data.env = env;
	data.type = CMD;
	data.buf = new_str("");
	if (scanner_loop(scan_list, &data) == OK)
		return (free_n_return(data.line, OK));
	return (free_n_return(data.line, ERR));
}
