#ifndef TREE_H
# define TREE_H

# define	INDENT_SIZE 2

//@func
/*
** < repr1.c > */

void	ast_node_repr(t_AST_NODE *node, int level);
/*
** < repr2.c > */

void	ast_command_repr(t_AST_COMMAND *cmd, int level);
void	ast_pipeline_repr(t_AST_SCRIPT *pipeline, int level);
void	ast_script_repr(t_AST_SCRIPT *script);
#endif