#include "minishell.h"

t_AST_expansion	*new_ast_expansion(char *parameter, int begin, int end)
{
	t_AST_expansion	*expansion;

	expansion = ft_calloc(sizeof(t_AST_expansion), 0);
	expansion->parameter = new_str(parameter);
	expansion->begin = begin;
	expansion->end = end;
	return (expansion);
}

t_AST_expansion	**new_ast_expansions(t_AST_expansion *expansions[])
{
	int				i;
	t_AST_expansion	**new;

	new = ft_calloc(sizeof(t_AST_expansion *), 0);
	if (expansions)
	{
		i = -1;
		while (expansions[++i])
			expansions_append(&new, expansions[i]);
	}
	return (new);
}

t_AST_NODE	*new_ast_word(
	const char *text, t_AST_expansion *expansions[])
{
	t_AST_NODE	*node;

	node = ft_calloc(sizeof(t_AST_NODE), 0);
	node->op = NOT_REDIR;
	node->type = WORD;
	node->text = new_str(text);
	if (expansions)
		node->expansions = new_ast_expansions(expansions);
	else
		node->expansions = NULL;
	return (node);
}

t_AST_NODE	*new_ast_redirect(
	const char *text, t_AST_expansion *expansions[], t_redirect_op op)
{
	t_AST_NODE	*node;

	node = new_ast_word(text, expansions);
	node->op = op;
	node->type = REDIRECT;
	return (node);
}
