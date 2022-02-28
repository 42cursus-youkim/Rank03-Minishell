#include "libft.h"

bool	is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (true);
	return (false);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_overflow(int n, int sign)
{
	return (
		(sign == -1 && n > 0)
		|| (sign == 1 && n < 0));
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
