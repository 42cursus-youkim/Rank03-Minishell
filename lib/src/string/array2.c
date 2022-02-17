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

//	append a string "str" to the end of the array "arr", free "str"
t_res	ft_arr_append_free(char **parr[], char *str)
{
	if (ft_arr_append(parr, str) == ERR)
		return (ERR);
	free(str);
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
