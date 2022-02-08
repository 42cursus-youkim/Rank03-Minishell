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

char	*ft_strdup(const char *from)
{
	int		i;
	char	*str;

	i = ft_strlen(from);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
		str[i] = from[i];
	return (str);
}
