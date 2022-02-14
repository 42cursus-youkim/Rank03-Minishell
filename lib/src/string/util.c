#include "libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (ERR);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	is_str_equal(const char *str1, const char *str2)
{
	const int	str1_len = ft_strlen(str1);
	const int	str2_len = ft_strlen(str2);
	int			i;

	if (!str1 || !str2 || str1_len != str2_len)
		return (false);
	i = -1;
	while (++i < str1_len)
		if (str1[i] != str2[i])
			return (false);
	return (true);
}

int	ft_strchr_i(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (ERR);
}

//	prints NULL-terminated array in fancy colors
void	ft_arr_print(char **arr)
{
	int			i;
	const int	len = ft_arr_len(arr);
	const int	pad = ft_digit_len(len - 1);

	if (!arr || len == ERR)
		return ;
	i = -1;
	while (arr[++i])
		printf(BHYEL "[%*d] " HGRN "%s\n" END, pad, i, arr[i]);
}
