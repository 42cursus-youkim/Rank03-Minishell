#include "libft.h"

char	**new_arr(char **arr)
{
	int			i;
	char		**new;

	new = malloc(sizeof(char *) * 1);
	if (!new)
		return (NULL);
	new[0] = NULL;
	if (arr)
	{
		i = -1;
		while (arr[++i])
			ft_arr_append(&new, arr[i]);
	}
	return (new);
}

//	free all elements of arr then itself
void	del_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	ft_arr_len(char **arr)
{
	int		i;

	if (!arr)
		return (ERR);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
