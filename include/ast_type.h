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

#endif