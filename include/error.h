#ifndef ERROR_H
# define ERROR_H

# define MINISHELL			"minishell: "
# define SYNTAX_ERROR		"syntax error near unexpected token"
# define QUOTE_ERROR		"unclosed quote: "
# define BRACE_ERROR		"unclosed brace: "
# define MULTILINE_ERROR	"multiline is not supported :(\n"
# define MALLOC_ERROR		"failed to allocate memory :(\n"

//@func
/*
** < error.c > */

t_res	error_msg_return(char *message[]);
t_res	error_malloc_msg(void);
#endif