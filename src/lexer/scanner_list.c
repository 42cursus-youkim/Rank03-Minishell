#include "minishell.h"

t_scan_node	*new_scan_node(char *str, t_AST_expansion **arr)
{
	t_scan_node	*new;

	new = (t_scan_node *)malloc(sizeof(t_scan_node));
	if (!new)
		return (NULL);
	new->text = str;
	new->expansion = arr;
	return (new);
}

void	del_scan_node(void *param)
{
	t_scan_node	*node;

	node = (t_scan_node *)param;
	free(node->text);
	if (node->expansion)
		del_expansion_arr(node->expansion);
	free(node);
}

void	scan_node_print(void *param)
{
	t_scan_node	*node;
	int			i;

	node = (t_scan_node *)param;
	printf("\"" HGRN "%s" END "\"\n", node->text);
	if (node->expansion)
	{
		i = -1;
		while (node->expansion[++i] != NULL)
			printf("(%s -> %d, %d)\n", node->expansion[i]->parameter,
				node->expansion[i]->begin, node->expansion[i]->end);
	}
}
