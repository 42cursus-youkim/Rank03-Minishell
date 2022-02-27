#include "libft.h"

char	*new_str(const char *src)
{
	int		i;
	char	*new;

	i = ft_strlen(src);
	new = ft_calloc(sizeof(char), i);
	if (!new)
		return (NULL);
	while (--i >= 0)
		new[i] = src[i];
	return (new);
}

/*	slice new string from begin to end
	returns NULL if begin and end is out of range
*/
char	*new_str_slice(char *str, int begin, int end)
{
	int			i;
	char		*new;
	const int	str_len = ft_strlen(str);

	if (str_len == ERR || begin < 0 || end < 0 || begin > end || end > str_len)
		return (NULL);
	i = end - begin;
	new = ft_calloc(sizeof(char), i);
	if (!new)
		return (NULL);
	while (--i >= 0)
		new[i] = str[begin + i];
	return (new);
}
