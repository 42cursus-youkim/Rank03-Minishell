#ifndef AST_NODE_H
# define AST_NODE_H

// # include "ast_type.h"

typedef struct s_AST_WORD
{
	char			*text;
	t_AST_expansion	**expansions;
}	t_AST_WORD;

typedef struct s_AST_REDIRECT
{
	char			*file;
	t_redirect_op	op;
}	t_AST_REDIRECT;

typedef struct s_AST_suffix
{
	t_AST_type			type;
	union
	{
		t_AST_WORD		word;
		t_AST_REDIRECT	redirection;
	}	u_data;
}	t_AST_suffix;

typedef struct s_AST_COMMAND
{
	t_AST_WORD		name;
	t_AST_REDIRECT	**prefixes;
	t_AST_suffix	**suffixes;
}	t_AST_COMMAND;

typedef struct s_AST_PIPELINE
{
	t_AST_COMMAND	**commands;
}	t_AST_PIPELINE;

typedef struct s_AST_SCRIPT_elem
{
	t_AST_type		type;
	union
	{
		t_AST_COMMAND	command;
		t_AST_PIPELINE	pipeline;
	}	u_data;
}	t_AST_SCRIPT_elem;

typedef struct s_AST_SCRIPT
{
	t_AST_SCRIPT_elem	**elems;
}	t_AST_SCRIPT;

#endif