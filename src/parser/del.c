#include "minishell.h"

void	del_ast_expansions(t_AST_expansion *expansions[])
{
	int		i;

	i = -1;
	while (expansions[++i])
	{
		free(expansions[i]->parameter);
		free(expansions[i]);
	}
	free(expansions);
}

void	del_ast_node(t_AST_NODE *node)
{
	if (!node)
		return ;
	free(node->text);
	if (node->expansions)
		del_ast_expansions(node->expansions);
	free(node);
}
