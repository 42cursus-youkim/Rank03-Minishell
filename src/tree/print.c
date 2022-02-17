#include "minishell.h"

static void	tree_rec(void *tree, t_AST_type type, int level)
{
	if (type == WORD || type == REDIRECT)
		return (ast_node_repr(tree, level + 1));
	if (type == COMMAND)
	{
		tree_rec(((t_AST_COMMAND *)tree)->name, WORD, level + 1);
		// tree_rec(((t_AST_COMMAND *)tree)->prefixes, WORD, level + 1);
	}
	return ;
}

void	ast_tree_print(void *tree, t_AST_type type)
{
	tree_rec(tree, type, -1);
}
