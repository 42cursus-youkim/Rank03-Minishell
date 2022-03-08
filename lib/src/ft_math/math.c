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

/*	long long overflow saturation
	-overflow: 0
	+overflow: -1
*/
static t_res	overflow_saturation(int temp, int num, int sign, int *n)
{
	if (temp < num)
	{
		if (sign == -1)
			*n = 0;
		else
			*n = -1;
		return (OK);
	}
	return (UNSET);
}

/*	pass reference to n to convert str to int
	ERR: str has non-digit char
*/
t_res	ft_atoi(const char *str, int *n)
{
	int			i;
	int			sign;
	long long	num;
	long long	temp;

	i = 0;
	num = 0;
	sign = 1;
	if (!str)
		return (ERR);
	while (ft_strchr_i("\t\n\v\f\r ", str[i]) >= 0)
		i++;
	if (ft_strchr_i("-+", str[i]) >= 0 && str[i++] == '-')
		sign = -1;
	while (is_digit(str[i]))
	{
		temp = num * 10 + (str[i++] - '0');
		if (overflow_saturation(temp, num, sign, n) == OK)
			return (OK);
		num = temp;
	}
	*n = sign * (int)num;
	if (str[i])
		return (ERR);
	return (OK);
}
