#include "minishell.h"

bool	is_1stchar_valid(char c)
{
	if (is_alpha(c) || c == '_' || c == '{' || c == '?')
		return (true);
	return (false);
}

bool	is_variable_char_valid(char c)
{
	if (is_alpha(c) || is_digit(c) || c == '_')
		return (true);
	return (false);
}

bool	is_scan_continuos(char *buf, char c)
{
	if (!c || (!is_quotes_open(NULL, buf) && !is_brace_open(buf)
			&& (is_whitespace(c) || is_metachar(c))))
		return (false);
	return (true);
}

t_res	free_n_return(char **str, t_res result)
{
	free(*str);
	return (result);
}

t_res	free_arr_n_return(char *arr[], t_res result)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	return (result);
}
