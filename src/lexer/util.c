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

bool	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
