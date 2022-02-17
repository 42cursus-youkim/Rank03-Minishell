#ifndef TREE_H
# define TREE_H

# define	INDENT_SIZE 2

//@func
/*
** < print.c > */

void	ast_tree_print(void *tree, t_AST_type type);
/*
** < repr1.c > */

void	ast_node_repr(t_AST_NODE *node, int level);
/*
** < repr2.c > */

void	ast_command_repr(t_AST_COMMAND *cmd, int level);
void	ast_pipeline_repr(t_AST_PIPELINE *pipeline, int level);
/*
** < util.c > */

char	*pad_whitespace(int len);
void	pad_repr(char **repr, int len);
#endif