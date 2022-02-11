#include "libft.h"

char	*new_str(const char *src)
{
	int		i;
	char	*new;

	i = ft_strlen(src);
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[i] = '\0';
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
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[i] = '\0';
	while (--i >= 0)
		new[i] = str[begin + i];
	return (new);
}

static int	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}

int	ft_str_append(char **pstr, char *src)
{
	const int	org_len = ft_strlen(*pstr);
	const int	src_len = ft_strlen(src);
	const int	new_len = org_len + src_len;
	char		*new;

	new = malloc((new_len + 1) * sizeof(char));
	if (!new)
		return (ERR);
	new[new_len] = '\0';
	ft_strcpy(new, *pstr);
	ft_strcpy(new + org_len, src);
	free(*pstr);
	*pstr = new;
	return (new_len);
}
