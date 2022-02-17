#ifndef PARSER_H
# define PARSER_H
//@func
/*
** < new.c > */

t_AST_COMMAND	*new_ast_command( t_AST_WORD *word, t_AST_REDIRECT **prefixes,
					t_AST_NODE **suffixes);
#endif