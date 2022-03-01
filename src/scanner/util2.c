#include "minishell.h"

bool	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_quotechar(char c)
{
	if (c == '\"' || c == '\'')
		return (true);
	return (false);
}

bool	is_tilde_expansion(t_scan_data *data, int i)
{
	if (data->line[i] == '~'
		&& is_str_equal(data->buf, "")
		&& !is_quotes_open(NULL, data->buf, QUOTE_CLOSE, '\0')
		&& (!data->line[i + 1] || data->line[i + 1] == ' '
			|| data->line[i + 1] == '/'))
		return (true);
	return (false);
}
