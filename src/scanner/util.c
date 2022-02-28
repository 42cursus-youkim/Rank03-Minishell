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

bool	is_brace_open(char *str)
{
	int		i;
	bool	open;

	i = -1;
	open = false;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '{')
		{
			open = true;
			i++;
		}
		if (open && str[i] == '}')
			open = false;
	}
	return (open);
}

t_res	list_element_create(
	t_list **element, char *buf, t_AST_expansion **expansions)
{
	char		*str;
	t_scan_node	*content;

	*element = NULL;
	str = new_str(buf);
	content = new_scan_node(str, expansions);
	*element = new_list(content);
	return (OK);
}

t_res	buf_to_list(t_list **list, char **buf)
{
	const int	buf_len = ft_strlen(*buf);
	t_list		*list_element;

	if (buf_len == 0)
		return (UNSET);
	list_element_create(&list_element, *buf, NULL);
	ft_list_append(list, list_element);
	free(*buf);
	*buf = new_str("");
	return (OK);
}

t_res	whitespace_scan(t_list **list, t_scan_data *data)
{
	int	i;

	i = data->idx;
	if (is_whitespace(data->line[i]) && !is_quotes_open(NULL, data->buf))
	{
		buf_to_list(list, &data->buf);
		while (is_whitespace(data->line[++i]))
			;
		data->idx = --i;
		return (OK);
	}
	return (UNSET);
}
