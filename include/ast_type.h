#ifndef AST_TYPE_H
# define AST_TYPE_H

typedef enum e_AST_type
{
	WORD = 0,
	PIPELINE,
	REDIRECT,
	COMMAND,
	SCRIPT,
}	t_AST_type;

typedef enum e_redirect_op
{
	REDIR_INPUT,
	REDIR_HEREDOC,
	REDIR_OUTPUT,
	REDIR_OUTPUT_APPEND,
	NOT_REDIR,
}	t_redirect_op;

typedef struct s_AST_expansion
{
	char	*parameter;
	int		begin;
	int		end;
}	t_AST_expansion;

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

#endif