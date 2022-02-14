#include "libft.h"

static char	*new_char_tostr(char c)
{
	char	*new;

	new = malloc(2 * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = c;
	new[1] = '\0';
	return (new);
}

char	*new_str_join(char **arr, char delimiter)
{
	int			i;
	char		*new;
	char		*delim;
	const int	arr_len = ft_arr_len(arr);

	if (!arr || !arr_len)
		return (NULL);
	new = new_str("");
	if (!new)
		return (NULL);
	delim = new_char_tostr(delimiter);
	i = -1;
	while (++i < arr_len - 1)
	{
		ft_str_append(&new, arr[i]);
		ft_str_append(&new, delim);
	}
	ft_str_append(&new, arr[i]);
	free(delim);
	return (new);
}

char	*new_str_join_freed(char *delimiter_str, int size, t_tempstr map[])
{
	int		i;
	char	*new;

	if (!map || !delimiter_str || size < 0)
		return (NULL);
	new = new_str("");
	if (!new)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		ft_str_append(&new, map[i].str);
		if (i < size - 1)
			ft_str_append(&new, delimiter_str);
		if (map[i].will_free)
			free(map[i].str);
	}
	return (new);
}
