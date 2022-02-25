#ifndef LEXER_H
# define LEXER_H

typedef struct s_expansion_scan_info
{
	char			**buf;
	char			*str;
	int				*idx;
	int				start_i;
	t_AST_expansion	**expansions;
	int				begin;
	int				end;

}	t_expansion_scan_info;

typedef struct s_metastr
{
	char	*str;
	char	*prev;
	int		i;
}	t_metastr;

typedef struct s_scan_node
{
	char				*text;
	t_AST_expansion		**expansions;
}	t_scan_node;

typedef struct s_token
{
	t_AST_type			type;
	char				*text;
	t_AST_expansion		**expansions;
}	t_token;

//@func
/*
** < dollar_scan1.c > */

t_res		dollar_scan(t_list **list, char **buf, char *str, int *idx);
/*
** < dollar_scan2.c > */

t_res		expansions_update_with_brace( t_expansion_scan_info *info, int end,
				bool brace);
t_res		expansion_location_init(t_expansion_scan_info *info, int *i);
bool		is_multi_expansions(t_expansion_scan_info info, int i);
/*
** < expansion.c > */

int			expansions_len(t_AST_expansion *expansions[]);
t_res		expansions_append(t_AST_expansion **parr[],
				t_AST_expansion *element);
t_res		expansions_append_free( t_AST_expansion **parr[],
				t_AST_expansion *element);
void		expansions_print(t_AST_expansion *expansions[]);
/*
** < lexer.c > */

t_token		*lexer(char *line);
/*
** < metachar_scan1.c > */

t_res		metachar_scan(t_list **list, char **buf, char *str, int *idx);
/*
** < metachar_scan2.c > */

t_res		metachar_attachable(char **pstr, char prev_c, char c);
t_res		metastr_init(t_metastr *metastr, char c);
bool		is_prev_metachar_attachable(char *str);
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
t_res		list_element_create( t_list **element, char *buf,
				t_AST_expansion **expansions);
t_res		buf_to_list(t_list **list, char **buf);
t_res		whitespace_scan(t_list **list, char **buf, char *str, int *idx);
/*
** < tokenizer.c > */

t_res		quotes_remove_loop(char **new, char *last_quote, bool *open,
				char c);
char		*new_quotes_remove(const char *str);
t_res		node_tokenize(t_token *tokens[], t_scan_node *node, int i);
t_token		*tokenizer(t_list *scan_list);
/*
** < tokenizer_util.c > */

t_AST_type	tokentype_check(t_scan_node *node);
void		tokens_print(t_token tokens[]);
void		del_tokens(t_token tokens[]);
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
t_res		free_n_return(char **str, t_res result);
t_res		free_arr_n_return(char *arr[], t_res result);
#endif