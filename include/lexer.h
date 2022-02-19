#ifndef LEXER_H
# define LEXER_H

typedef struct	s_expansion_scan_info
{
	char			**buf;
	char			*str;
	int				*idx;
	int				start_i;
	t_AST_expansion	**expansions;
	int				begin;
	int				end;

}	t_expansion_scan_info;

typedef struct s_scan_node
{
	char				*text;
	t_AST_expansion		**expansions;
}	t_scan_node;

typedef struct s_token
{
	t_AST_type	type;
	char		*text;
}	t_token;

//@func
/*
** < expansion.c > */

int			expansions_len(t_AST_expansion *expansions[]);
t_res		expansions_append_free(t_AST_expansion **parr[],
				t_AST_expansion *element);
void		expansions_print(t_AST_expansion *expansions[]);
/*
** < lexer.c > */

t_token		*tokenizer(char *arr[]);
/*
** < lexer_tokenizer.c > */

t_AST_type	tokentype_check(const char *str);
int			quotes_index(const char *str);
bool		is_expand_parameter(const char *str);
void		tokens_print(t_token tokens[]);
void		del_tokens(t_token tokens[]);
/*
** < scanner.c > */

t_res		scanner(t_list **scan_list, char *line);
/*
** < scanner_list.c > */

t_scan_node	*new_scan_node(char *str, t_AST_expansion **arr);
void		del_scan_node(void *param);
void		scan_node_print(void *param);
/*
** < scanner_util.c > */

bool		is_quotes_open(char *last_quote, char *str);
bool		is_brace_open(char *str);
t_res		buf_to_list(t_list **list, char **buf);
t_res		whitespace_scan(t_list **list, char **buf, char *str, int *idx);
/*
** < scanner_util2.c > */

t_res		metachar_scan(t_list **list, char **buf, char *str, int *idx);
/*
** < scanner_util3.c > */

t_res		expansion_scan(t_list **list, char **buf, char *str, int *idx);
t_res		dollar_scan(t_list **list, char **buf, char *str, int *idx);
/*
** < util.c > */

bool		is_metachar(char c);
bool		is_whitespace(char c);
bool		is_quotechar(char c);
bool		is_alpha(char c);
bool		is_digit(char c);
/*
** < util2.c > */

bool		is_1stchar_valid(char c);
bool		is_variable_char_valid(char c);
bool		is_scan_continuos(char *buf, char c);
bool		is_multi_expansions(t_expansion_scan_info info, int i);
#endif