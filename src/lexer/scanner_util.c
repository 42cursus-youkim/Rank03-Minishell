#include "minishell.h"

bool	is_quotes_open(char *last_quote, char *str)
{
	char	quote;
	bool	open;
	int		i;

	i = -1;
	quote = '\0';
	open = false;
	while (str[++i])
	{
		if (is_quotechar(str[i]) && !open)
		{
			quote = str[i];
			open = true;
			continue ;
		}
		if (is_quotechar(str[i]) && str[i] == quote)
			open = false;
	}
	if (last_quote)
		*last_quote = quote;
	return (open);
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
	if (is_whitespace(str[i]) && !is_quotes_open(NULL, *buf))
	{
		buf_to_list(list, buf);
		while (is_whitespace(str[++i]))
			;
		*idx = --i;
		return (OK);
	}
	return (UNSET);
}
