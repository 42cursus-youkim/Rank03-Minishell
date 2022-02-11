#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	t_tokentype	type;	
	char		*text;
}	t_token;

//@func
/*
** < lexer.c > */

t_token	*tokenizer(char *arr[]);
/*
** < lexer_tokenizer.c > */

bool	is_metachar(t_token *token, const char *str);
bool	is_quotes(const char *str);
bool	is_expand_parameter(const char *str);
void	token_print(t_token token[]);
void	del_token(t_token token[]);
#endif