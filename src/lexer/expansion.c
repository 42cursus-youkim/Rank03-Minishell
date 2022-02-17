#include "minishell.h"

t_AST_expansion	*new_expansion(char *str, int begin, int end)
{
	t_AST_expansion	*new;

	new = (t_AST_expansion *)ft_calloc(sizeof(t_AST_expansion), 1);
	if (!new)
		return (NULL);
	new->parameter = str;
	new->begin = begin;
	new->end = end;
	return (new);
}

int	expansion_arr_len(t_AST_expansion *arr[])
{
	int	i;

	if (!arr)
		return (ERR);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_res	expansion_arr_append(t_AST_expansion **parr[], t_AST_expansion *element)
{
	const int		arr_len = expansion_arr_len(*parr);
	t_AST_expansion	**new;
	int				i;

	if (arr_len == ERR)
		return (ERR);
	new = (t_AST_expansion **)ft_calloc(sizeof(t_AST_expansion), arr_len + 1);
	if (!new)
		return (ERR);
	i = -1;
	while (++i < arr_len)
		new[i] = new_expansion((*parr)[i]->parameter,
				(*parr)[i]->begin, (*parr)[i]->end);
	new[i] = new_expansion(element->parameter, element->begin, element->end);
	del_expansion_arr(*parr);
	*parr = new;
	return (OK);
}

t_AST_expansion	**new_expansion_arr(t_AST_expansion **arr)
{
	t_AST_expansion	**new;
	int				i;

	new = (t_AST_expansion **)ft_calloc(sizeof(t_AST_expansion), 0);
	if (!new)
		return (NULL);
	if (arr)
	{
		i = -1;
		while (arr[++i])
			expansion_arr_append(&new, arr[i]);
	}
	return (new);
}

void	del_expansion_arr(t_AST_expansion *arr[])
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}
