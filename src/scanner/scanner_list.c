#include "minishell.h"

t_scan_node	*new_scan_node(char *str, t_AST_expansion **arr)
{
	t_scan_node	*new;

	new = ft_calloc(sizeof(t_scan_node), 0);
	if (!new)
		return (NULL);
	new->text = str;
	new->expansions = arr;
	return (new);
}

void	del_scan_node(void *param)
{
	t_scan_node	*node;

	node = (t_scan_node *)param;
	free(node->text);
	if (node->expansions)
		del_ast_expansions(node->expansions);
	free(node);
}

void	scan_node_print(void *param)
{
	t_scan_node	*node;

	node = (t_scan_node *)param;
	printf("\"" HGRN "%s" END "\"\n", node->text);
	if (node->expansions)
		expansions_print(node->expansions);
}
