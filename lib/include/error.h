#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
# include <string.h>
# include "type.h"

# define MINISHELL			"minishell: "
# define SYNTAX_ERROR		"syntax error near unexpected token"
# define QUOTE_ERROR		"unclosed quote: "
# define BRACE_ERROR		"unclosed brace: "
# define MULTILINE_ERROR	"multiline is not supported :("
# define MALLOC_ERROR		"failed to allocate memory :("
# define SUBSTITUTION_ERROR	": bad substitution"

//@func
/*
** < error.c > */

t_res	error_syscall(char *category);
#endif