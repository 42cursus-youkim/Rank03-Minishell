#ifndef AST_NODE_H
# define AST_NODE_H

typedef struct s_AST_NODE
{
	t_redirect_op	op;
	t_AST_type		type;
	char			*text;
	t_AST_expansion	**expansions;
}	t_AST_NODE;

typedef struct s_AST_COMMAND
{
	t_AST_NODE	*name;
	t_AST_NODE	**prefixes;
	t_AST_NODE	**suffixes;
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