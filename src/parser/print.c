#include "minishell.h"

static char	*new_range_repr(int begin, int end)
{
	return (new_str_join_freed("", 5, (t_tempstr []){
			{"(", 0},
			{new_itoa(begin), 1},
			{"~", 0},
			{new_itoa(end), 1},
			{")", 0},
		}));
}

static char	*new_ast_expansion_repr(t_AST_expansion **expansions)
{
	int		i;
	char	*repr;

	repr = new_str("");
	if (!expansions)
		return (repr);
	i = -1;
	while (expansions[++i])
		ft_str_extend_freed(&repr, new_str_join_freed("", 5, (t_tempstr[]){
			{" -" HGRN, 0},
			{expansions[i]->parameter, 0},
			{END, 0},
			{new_range_repr(expansions[i]->begin, expansions[i]->end), 1},
			{"\n", 0},
			}));
	return (repr);
}

static char	*new_ast_word_repr(t_AST_NODE *node)
{
	char	*repr;

	repr = new_str_join((char *[]){
			BWHT, node->text, END, NULL}, '\0');
	if (!node->expansions)
		return (repr);
	ft_str_append(&repr, '\n');
	ft_str_extend_freed(&repr, new_ast_expansion_repr(node->expansions));
	return (repr);
}

static char	*ast_redirect_repr(t_AST_NODE *node)
{
	static char	*op_str[] = {
		"◀️ ", "◀️◀️", "▶️ ", "▶️▶️",
	};

	return (new_str_join_freed("", 5, (t_tempstr []){
			{BYEL, 0},
			{node->text, 0},
			{" ", 0},
			{op_str[node->op], 0},
			{END, 0},
			{new_ast_expansion_repr(node->expansions), 1},
		}));
}

char	*new_ast_node_repr(t_AST_NODE *node)
{
	if (node->type == WORD)
		return (new_ast_word_repr(node));
	else if (node->type == REDIRECT)
		return (ast_redirect_repr(node));
	else
		return (NULL);
}
