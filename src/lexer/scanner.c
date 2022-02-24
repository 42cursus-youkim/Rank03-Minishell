#include "minishell.h"

static t_res	error_unclosed(char c, char **buf)
{
	char	*quote_str;

	quote_str = (char []){'(', c, ')', ':', ' ', '\0'};
	return (free_n_return(buf, error_msg_return((char *[]){
				MINISHELL,
				QUOTE_ERROR,
				quote_str,
				MULTILINE_ERROR,
				END,
				NULL})));
}

static t_res	scan_last_check(t_list **scan_list, char **buf)
{
	char	last_quote;

	if (is_quotes_open(&last_quote, *buf))
		return (error_unclosed(last_quote, buf));
	if (buf_to_list(scan_list, buf) == ERR)
		return (ERR);
	free(*buf);
	return (OK);
}

static t_res	scanner_loop(t_list **scan_list, char *line, char **buf, int *i)
{
	t_res	scan_res;

	while (line[++*i])
	{
		scan_res = whitespace_scan(scan_list, buf, line, i);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (ERR);
		scan_res = dollar_scan(scan_list, buf, line, i);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (ERR);
		scan_res = metachar_scan(scan_list, buf, line, i);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (ERR);
		if (ft_str_append(buf, line[*i]) == ERR)
			return (free_n_return(buf, error_msg_return(MALLOC_ERROR_MSG)));
	}
	return (scan_last_check(scan_list, buf));
}

t_res	scanner(t_list **scan_list, char *line)
{
	char	*buf;
	int		i;

	buf = new_str("");
	if (!buf)
		return (error_msg_return(MALLOC_ERROR_MSG));
	i = -1;
	return (scanner_loop(scan_list, line, &buf, &i));
}
