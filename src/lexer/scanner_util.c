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
	if (!str)
		return (error_msg_return(MALLOC_ERROR_MSG));
	content = new_scan_node(str, expansions);
	if (!content)
		return (free_n_return(&str, error_msg_return(MALLOC_ERROR_MSG)));
	*element = new_list(content);
	if (!element)
	{
		del_scan_node(content);
		return (error_msg_return(MALLOC_ERROR_MSG));
	}
	return (OK);
}

t_res	buf_to_list(t_list **list, char **buf)
{
	const int	buf_len = ft_strlen(*buf);
	t_list		*list_element;

	if (buf_len == 0)
		return (UNSET);
	if (list_element_create(&list_element, *buf, NULL) == ERR)
		return (free_n_return(buf, ERR));
	ft_list_append(list, list_element);
	free(*buf);
	*buf = new_str("");
	if (!*buf)
		return (error_msg_return(MALLOC_ERROR_MSG));
	return (OK);
}

t_res	whitespace_scan(t_list **list, char **buf, char *str, int *idx)
{
	int	i;

	i = *idx;
	if (is_whitespace(str[i]) && !is_quotes_open(NULL, *buf))
	{
		if (buf_to_list(list, buf) == ERR)
			return (ERR);
		while (is_whitespace(str[++i]))
			;
		*idx = --i;
		return (OK);
	}
	return (UNSET);
}
