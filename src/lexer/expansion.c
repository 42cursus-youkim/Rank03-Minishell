#include "minishell.h"

void	del_expansion_arr(t_AST_expansion *arr[])
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}
