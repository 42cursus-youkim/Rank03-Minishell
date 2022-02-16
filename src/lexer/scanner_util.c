#include "minishell.h"

static int	quotes_count(char *str, char quote)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == quote)
			count++;
	return (count);
}

bool	is_quotes_open(char *str)
{
	const int	single_quotes = quotes_count(str, '\'');
	const int	double_quotes = quotes_count(str, '\"');

	if (single_quotes % 2 || double_quotes % 2)
		return (true);
	return (false);
}

t_res	buf_to_list(t_list **list, char **buf)
{
	const int	buf_len = ft_strlen(*buf);

	if (buf_len == 0)
		return (UNSET);
	ft_list_append(list, new_list(new_scan_node(new_str(*buf), NULL)));
	free(*buf);
	*buf = new_str("");
	return (OK);
}

t_res	whitespace_scan(t_list **list, char **buf, char *str, int *idx)
{
	int	i;

	i = *idx;
	if (is_whitespace(str[i]) && !is_quotes_open(*buf))
	{
		buf_to_list(list, buf);
		while (is_whitespace(str[++i]))
			;
		*idx = --i;
		return (OK);
	}
	return (UNSET);
}
