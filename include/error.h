#ifndef ERROR_H
# define ERROR_H

# define MINISHELL			"minishell: "
# define SYNTAX_ERROR		"syntax error near unexpected token"
# define QUOTE_ERROR		"unclosed quote: "
# define BRACE_ERROR		"unclosed brace: "
# define MULTILINE_ERROR	"multiline is not supported :(\n"
# define MALLOC_ERROR		"failed to allocate memory :(\n"
# define SUBSTITUTION_ERROR	": bad substitution\n"

//@func
/*
** < error.c > */

t_res	error_msg_return(char *message[]);
t_res	error_malloc_msg(void);
t_res	error_with_exitcode(char *message[], t_dict *env, int exitcode);
#endif