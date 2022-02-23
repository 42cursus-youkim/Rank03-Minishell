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

char	*new_itoa(int n)
{
	char	*str;
	int		digit;
	long	num;

	num = n;
	if (num == 0)
		return (new_str("0"));
	digit = ft_digit_len(num);
	if (num < 0)
		digit++;
	str = ft_calloc(sizeof(char), digit);
	if (!str)
		return (NULL);
	if (num < 0)
	{
		num = -num;
		str[0] = '-';
	}
	while (num > 0)
	{
		str[--digit] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}

char	*ft_bool_to_str(bool b)
{
	static char	*value[] = {
		BRED "false" END,
		HGRN "true" END};

	return (value[b]);
}
