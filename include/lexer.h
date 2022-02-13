#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	t_AST_type	type;
	char		*text;
}	t_token;

//@func
/*
** < lexer.c > */

t_token		*tokenizer(char *arr[]);
/*
** < lexer_tokenizer.c > */

t_AST_type	tokentype_check(const char *str);
bool		is_quotes(const char *str);
bool		is_expand_parameter(const char *str);
void		tokens_print(t_token tokens[]);
void		del_tokens(t_token tokens[]);
#endif