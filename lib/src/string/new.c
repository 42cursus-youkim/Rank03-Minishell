#include "libft.h"

char	*ft_strdup(const char *src)
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

static int	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}

int	ft_strappend(char **pstr, char *src)
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
