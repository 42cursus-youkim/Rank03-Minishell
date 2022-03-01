#include "minishell.h"

t_res	expansions_to_array(char **parr[], t_AST_NODE *node)
{
	const int	len = ft_strlen(node->text);
	int			i;
	int			begin;
	char		*buf;

	i = -1;
	begin = 0;
	while (node->expansions[++i])
	{
		buf = new_str_slice(node->text, begin, node->expansions[i]->begin);
		ft_arr_append_free(parr, buf);
		buf = new_str_slice(node->text,
				node->expansions[i]->begin, node->expansions[i]->end + 1);
		ft_arr_append_free(parr, buf);
		begin = node->expansions[i]->end + 1;
	}
	buf = new_str_slice(node->text, begin, len);
	ft_arr_append_free(parr, buf);
	return (OK);
}

bool	is_substitution_valid(char *str)
{
	const int	len = ft_strlen(str);
	int			i;

	if (str[len - 1] != '}')
		return (true);
	if (len == 3)
		return (false);
	i = 2;
	if (!is_1stchar_valid(str[i]) || str[i] == '{')
		return (false);
	while (++i < len - 1)
	{
		if (!is_variable_char_valid(str[i]))
			return (false);
	}
	return (true);
}

t_quote_status	quote_status_recur(char **arr, int i)
{
	bool			open;
	t_quote_status	status;
	char			init_quote;

	init_quote = '\0';
	if (i == 1)
		open = is_quotes_open(NULL, arr[i - 1], QUOTE_CLOSE, init_quote);
	else
	{
		status = quote_status_recur(arr, i - 2);
		if (status == QUOTE_OPEN)
			init_quote = '\"';
		open = is_quotes_open(NULL, arr[i - 1], status, init_quote);
	}
	if (open)
		return (QUOTE_OPEN);
	return (QUOTE_CLOSE);
}

char	*new_whitespaces_remove(char *str)
{
	int		i;
	char	*new;

	new = new_str("");
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			ft_str_append(&new, ' ');
			while (str[++i] == ' ')
				;
		}
		if (str[i])
			ft_str_append(&new, str[i]);
	}
	return (new);
}
