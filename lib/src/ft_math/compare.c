#include "libft.h"

int	ft_digit_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
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
