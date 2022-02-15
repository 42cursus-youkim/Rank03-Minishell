#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	t_AST_type	type;
	char		*text;
}	t_token;

//@func
/*
** < lexer_scanner.c > */

t_res		buf_to_arr(char **parr[], char **buf);
t_res		whitespace_scan(char **arr[], char **buf, char *str, int *idx);
t_res		metachar_scan(char **arr[], char **buf, char *str, int *idx);
/*
** < lexer.c > */

t_res		scanner(char **scan_data[], char *line);
t_token		*tokenizer(char *arr[]);
/*
** < lexer_tokenizer.c > */

t_AST_type	tokentype_check(const char *str);
int			quotes_index(const char *str);
bool		is_expand_parameter(const char *str);
void		tokens_print(t_token tokens[]);
void		del_tokens(t_token tokens[]);
/*
** < util.c > */

bool		is_quotes_open(char *str);
bool		is_metachar(char c);
bool		is_whitespace(char c);
#endif