#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

typedef enum e_tokentype
{
	WORD = 0,
	PIPELINE,
	REDIRECT,
	COMMAND,
}	t_tokentype;

#endif