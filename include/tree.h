#ifndef TREE_H
# define TREE_H

//@func
/*
** < print.c > */

void	ast_tree_print(void *tree, t_AST_type type, int level);
/*
** < repr.c > */

void	ast_node_repr(t_AST_NODE *node, int level);
/*
** < util.c > */

char	*pad_whitespace(int len);
void	pad_repr(char **repr, int len);
#endif