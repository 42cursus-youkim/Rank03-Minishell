#include "libft.h"

/* append a string "str" to the end of the array "arr"
*/
t_res	ft_arr_append(char **parr[], char *str)
{
	const int	arr_len = ft_arr_len(*parr);
	const int	total_len = arr_len + 1;
	char		**new;
	int			i;

	if (arr_len == ERR)
		return (ERR);
	new = malloc((total_len + 1) * sizeof(char *));
	if (!new)
		return (ERR);
	new[total_len] = NULL;
	i = -1;
	while (++i < arr_len)
		new[i] = new_str((*parr)[i]);
	new[i] = new_str(str);
	del_arr(*parr);
	*parr = new;
	return (OK);
}

/*	extends str array "src" to "arr"
	ex: [a, b] + [c, d] = [a, b, c, d]
*/
t_res	ft_arr_extend(char **parr[], char *src[])
{
	const int	arr_len = ft_arr_len(*parr);
	const int	src_len = ft_arr_len(src);
	const int	total_len = arr_len + src_len;
	char		**new;
	int			i;

	if (arr_len == ERR || src_len == ERR)
		return (ERR);
	new = malloc((total_len + 1) * sizeof(char *));
	if (!new)
		return (ERR);
	new[total_len] = NULL;
	i = -1;
	while (++i < arr_len)
		new[i] = new_str((*parr)[i]);
	i = -1;
	while (++i < src_len)
		new[arr_len + i] = new_str(src[i]);
	del_arr(*parr);
	*parr = new;
	return (OK);
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
