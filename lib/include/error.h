#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
# include <string.h>

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

void	error_msg_category(char *category, char *msg);
void	error_syscall(char *category);
#endif