#include "minishell.h"

int	expansions_len(t_AST_expansion *expansions[])
{
	int	i;

	if (!expansions)
		return (ERR);
	i = 0;
	while (expansions[i])
		i++;
	return (i);
}

t_res	expansions_append(t_AST_expansion **parr[], t_AST_expansion *element)
{
	const int		arr_len = expansions_len(*parr);
	t_AST_expansion	**new;
	int				i;

	if (arr_len == ERR)
		return (ERR);
	new = ft_calloc(sizeof(t_AST_expansion), arr_len + 1);
	if (!new)
		return (ERR);
	i = -1;
	while (++i < arr_len)
		new[i] = new_ast_expansion(
				(*parr)[i]->parameter, (*parr)[i]->begin, (*parr)[i]->end);
	new[i] = new_ast_expansion(
			element->parameter, element->begin, element->end);
	if (!new[i])
	{
		del_ast_expansions(new);
		return (ERR);
	}
	del_ast_expansions(*parr);
	*parr = new;
	return (OK);
}

t_res	expansions_append_free(
	t_AST_expansion **parr[], t_AST_expansion *element)
{
	if (expansions_append(parr, element) == ERR)
		return (ERR);
	free(element->parameter);
	free(element);
	return (OK);
}

void	expansions_print(t_AST_expansion *expansions[])
{
	int	i;

	i = -1;
	while (expansions[++i])
		printf(BLU "\t[%d] (%s -> %d, %d)\n" END, i, expansions[i]->parameter,
			expansions[i]->begin, expansions[i]->end);
}
