#include "libft.h"

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

//	pass reference to n to convert str to int
t_res	ft_atoi(const char *str, int *n)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	if (!str)
		return (ERR);
	while (ft_strchr_i("\t\n\v\f\r ", str[i]) >= 0)
		i++;
	if (ft_strchr_i("-+", str[i]) >= 0)
		if (str[i++] == '-')
			sign = -1;
	while (is_digit(str[i]))
		num = num * 10 + (str[i++] - '0');
	*n = sign * num;
	if (is_overflow(*n, sign))
		return (ERR);
	return (OK);
}
