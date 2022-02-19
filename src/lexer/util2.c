#include "minishell.h"

bool	is_1stchar_valid(char c)
{
	if (is_alpha(c) || c == '{' || c == '_')
		return (true);
	return (false);
}

bool	is_variable_char_valid(char c)
{
	if (is_alpha(c) || is_digit(c) || c == '_' || c == '}')
		return (true);
	return (false);
}

bool	is_scan_continuos(char *buf, char c)
{
	if (!c || (!is_quotes_open(NULL, buf)
			&& (is_whitespace(c) || is_metachar(c))))
		return (false);
	return (true);
}

bool	is_multi_expansions(t_expansion_scan_info info, int i)
{
	char	last_quote;

	if (info.str[i] == '$' && is_1stchar_valid(info.str[i + 1])
		&& (!is_quotes_open(&last_quote, *info.buf) || last_quote != '\''))
		return (true);
	return (false);
}
