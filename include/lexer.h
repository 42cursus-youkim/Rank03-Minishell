#ifndef LEXER_H
# define LEXER_H

typedef struct s_scan_node
{
	char				*text;
	t_AST_expansion		**expansion;
}	t_scan_node;

typedef struct s_token
{
	t_AST_type	type;
	char		*text;
}	t_token;

//@func
/*
** < expansion.c > */

t_AST_expansion	*new_expansion(char *str, int begin, int end);
int				expansion_arr_len(t_AST_expansion *arr[]);
t_res			expansion_arr_append(t_AST_expansion **parr[],
					t_AST_expansion *element);
t_AST_expansion	**new_expansion_arr(t_AST_expansion **arr);
void			del_expansion_arr(t_AST_expansion *arr[]);
/*
** < lexer.c > */

t_token			*tokenizer(char *arr[]);
/*
** < lexer_tokenizer.c > */

t_AST_type		tokentype_check(const char *str);
int				quotes_index(const char *str);
bool			is_expand_parameter(const char *str);
void			tokens_print(t_token tokens[]);
void			del_tokens(t_token tokens[]);
/*
** < scanner.c > */

t_res			scanner(t_list **scan_list, char *line);
/*
** < scanner_list.c > */

t_scan_node		*new_scan_node(char *str, t_AST_expansion **arr);
void			del_scan_node(void *param);
void			scan_node_print(void *param);
/*
** < scanner_util.c > */

bool			is_quotes_open(char *last_quote, char *str);
t_res			buf_to_list(t_list **list, char **buf);
t_res			whitespace_scan(t_list **list, char **buf, char *str,
					int *idx);
/*
** < scanner_util2.c > */

t_res			metachar_scan(t_list **list, char **buf, char *str, int *idx);
/*
** < util.c > */

bool			is_metachar(char c);
bool			is_whitespace(char c);
bool			is_quotechar(char c);
#endif