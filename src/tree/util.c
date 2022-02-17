#include "minishell.h"

char	*pad_whitespace(int len)
{
	int		i;
	char	*str;

	str = new_str("");
	i = -1;
	while (++i < len)
		ft_str_append(&str, ' ');
	return (str);
}

void	pad_repr(char **repr, int len)
{
	int		i;
	char	**arr;
	char	**new;

	arr = new_str_split(*repr, '\n');
	new = new_arr(NULL);
	i = -1;
	while (arr[++i])
		ft_arr_append_free(&new, new_str_join_freed("", 2, (t_tempstr[]){
			{pad_whitespace(len), 1},
			{arr[i], 0},
			}));
	free(*repr);
	*repr = new_str_join(new, '\n');
	del_arr(new);
	del_arr(arr);
}
