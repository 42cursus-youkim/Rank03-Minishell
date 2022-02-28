#ifndef AST_TYPE_H
# define AST_TYPE_H

typedef int	t_fd;

typedef enum e_AST_type
{
	WORD = 0,
	PIPELINE,
	REDIRECT,
	COMMAND,
	SCRIPT,
	TYPE_START = -1,
	TYPE_END = -2,
}	t_AST_type;

typedef enum e_redirect_op
{
	REDIR_INPUT = 0,
	REDIR_HEREDOC = 1,
	REDIR_OUTPUT = 2,
	REDIR_OUTPUT_APPEND = 3,
	NOT_REDIR = -1,
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
	t_fd		io[IO_SIZE];
}	t_AST_COMMAND;

typedef struct s_AST_SCRIPTS
{
	t_AST_COMMAND	**commands;
	int				commands_len;
}	t_AST_SCRIPT;

#endif