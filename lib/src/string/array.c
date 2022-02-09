#include "libft.h"

/*	adds all elements of src to arr
	returns newly extended arr
*/
// char	**ft_arr_extend(char ***parr, char **src)
// {
// 	char	**new;

// }

// char	*ft_arr_join(char **arr, char delim)
// {


// }

//	free all elements of arr then arr itself
void	ft_arr_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
