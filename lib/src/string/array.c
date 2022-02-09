#include "libft.h"

/*	extends all elements of src to arr
*/
t_res	ft_arr_extend(char ***parr, char **src)
{
	const int	arr_len = ft_arr_len(*parr);
	const int	src_len = ft_arr_len(src);
	const int	total_len = arr_len + src_len;
	char		**new;
	int			i;

	if (arr_len == ERR || src_len == ERR)
		return (ERR);
	new = malloc((arr_len + src_len + 1) * sizeof(char *));
	if (!new)
		return (ERR);
	new[total_len] = NULL;
	i = -1;
	while (++i < arr_len)
		new[i] = ft_strdup((*parr)[i]);
	i = -1;
	while (++i < src_len)
		new[arr_len + i] = ft_strdup(src[i]);
	ft_arr_free(*parr);
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

//	free all elements of arr then itself
void	ft_arr_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
