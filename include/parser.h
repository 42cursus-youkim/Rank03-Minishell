#ifndef PARSER_H
# define PARSER_H
//@func
/*
** < new.c > */

t_AST_NODE		*new_ast_word( const char *text,
					t_AST_expansion **expansions);
t_AST_NODE		*new_ast_redirect( const char *text,
					t_AST_expansion **expansions, t_redirect_op op);
t_AST_COMMAND	*new_ast_command( t_AST_NODE *name, t_AST_NODE **prefixes,
					t_AST_NODE **suffixes);
/*
** < print.c > */

char			*new_ast_node_repr(t_AST_NODE *node);
#endif