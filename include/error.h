#ifndef ERROR_H
# define ERROR_H

# define MINISHELL			BRED"minishell: "
# define SYNTAX_ERROR		"syntax error near unexpected token"
# define QUOTE_ERROR		"unclosed quote: "
# define BRACE_ERROR		"unclosed brace: "
# define MULTILINE_ERROR	"multiline is not supported :(\n"
# define MALLOC_ERROR		"failed to allocate memory :(\n"

# define MALLOC_ERROR_MSG	(char *[]){MINISHELL, MALLOC_ERROR, END, NULL}

typedef enum e_error_bit
{
	E_ONE = 0x1,
	E_TWO = 0x10,
	E_THREE = 0x100,
}	t_error_bit;

//@func
/*
** < error.c > */

t_res	error_msg_return(char *message[]);
#endif