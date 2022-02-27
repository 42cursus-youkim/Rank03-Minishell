#include "minishell.h"

static t_res	error_unclosed(char c, t_scan_data *data)
{
	char	*quote_str;

	quote_str = (char []){'(', c, ')', ':', ' ', '\0'};
	data->env_flag = true;
	return (free_n_return(&data->buf, error_with_exitcode((char *[]){
				BRED, MINISHELL, QUOTE_ERROR, quote_str,
				MULTILINE_ERROR, END, NULL}, data->env, 2)));
}

static t_res	scan_last_check(t_list **scan_list, t_scan_data *data)
{
	char	last_quote;

	if (is_quotes_open(&last_quote, data->buf))
		return (error_unclosed(last_quote, data));
	if (buf_to_list(scan_list, &data->buf) == ERR)
		return (ERR);
	free(data->buf);
	return (OK);
}

static t_res	scanner_loop(t_list **scan_list, t_scan_data *data)
{
	t_res	scan_res;

	while (data->line[++(data->idx)])
	{
		scan_res = whitespace_scan(scan_list, data);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (ERR);
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
		if (ft_str_append(&data->buf, data->line[data->idx]) == ERR)
			return (free_n_return(&data->buf, ERR));
	}
	return (scan_last_check(scan_list, data));
}

t_res	scanner(t_list **scan_list, char *line, t_dict *env)
{
	t_scan_data	data;
	t_res		res;

	data.line = line;
	data.idx = -1;
	data.env = env;
	data.env_flag = false;
	data.type = CMD;
	data.buf = new_str("");
	if (!data.buf)
	{
		env_set_exitcode(env, EXIT_FAILURE);
		return (ERR);
	}
	res = scanner_loop(scan_list, &data);
	if (res == OK)
		return (OK);
	if (!data.env_flag)
		env_set_exitcode(env, EXIT_FAILURE);
	return (ERR);
}
