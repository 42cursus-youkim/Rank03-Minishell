#include "minishell.h"

static t_res	free_n_return(char **str, t_res result)
{
	free(*str);
	return (result);
}

static t_res	error_unclosed(char c, char **buf)
{
	printf(BRED "minishell: unclosed quote(%c): ", c);
	printf("multiline is not supported :(\n" END);
	return (free_n_return(buf, ERR));
}

static t_res	scanner_loop(t_list **scan_list, char *line, char **buf, int *i)
{
	t_res	scan_res;
	char	last_quote;

	while (line[++*i])
	{
		if (whitespace_scan(scan_list, buf, line, i) == OK)
			continue ;
		if (dollar_scan(scan_list, buf, line, i) == OK)
			continue ;
		scan_res = metachar_scan(scan_list, buf, line, i);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (free_n_return(buf, ERR));
		ft_str_append(buf, line[*i]);
	}
	if (is_quotes_open(&last_quote, *buf))
		return (error_unclosed(last_quote, buf));
	buf_to_list(scan_list, buf);
	return (free_n_return(buf, OK));
}

t_res	scanner(t_list **scan_list, char *line)
{
	char	*buf;
	int		i;

	buf = new_str("");
	i = -1;
	return (scanner_loop(scan_list, line, &buf, &i));
}
