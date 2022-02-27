#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	t_AST_type			type;
	char				*text;
	t_AST_expansion		**expansions;
}	t_token;

//@func
/*
** < lexer.c > */

t_token		*lexer(char *line, t_dict *env);
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
#endif