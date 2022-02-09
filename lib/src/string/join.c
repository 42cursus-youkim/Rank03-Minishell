#include "libft.h"

static char	*ft_char_to_str(char c)
{
	char	*new;

	new = malloc(2 * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = c;
	new[1] = '\0';
	return (new);
}

char	*ft_arr_join(char **arr, char delimiter)
{
	int			i;
	char		*new;
	char		*delim;
	const int	arr_len = ft_arr_len(arr);

	printf("arr_len: %d\n", arr_len);
	if (!arr || !arr_len)
		return (NULL);
	new = ft_strdup("");
	delim = ft_char_to_str(delimiter);
	i = -1;
	while (++i < arr_len - 1)
	{
		ft_strappend(&new, arr[i]);
		ft_strappend(&new, delim);
	}
	ft_strappend(&new, arr[i]);
	free(delim);
	return (new);
}
