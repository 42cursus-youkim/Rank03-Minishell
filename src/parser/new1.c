#include "minishell.h"

t_AST_expansion	*new_ast_expansion(char *paramameter, int begin, int end)
{
	t_AST_expansion	*expansion;

	expansion = malloc(sizeof(t_AST_expansion));
	expansion->parameter = paramameter;
	expansion->begin = begin;
	expansion->end = end;
	return (expansion);
}

t_AST_expansion	**new_ast_expansions(t_AST_expansion *expansions[])
{
	int				i;
	t_AST_expansion	**new;

	new = malloc(sizeof(t_AST_expansion *));
	if (!expansions)
		return (NULL);
	i = -1;
	while (expansions[++i])
		new[i] = new_ast_expansion(
				expansions[i]->parameter,
				expansions[i]->begin, expansions[i]->end);
	return (expansions);
}

t_AST_NODE	*new_ast_word(
	const char *text, t_AST_expansion *expansions[])
{
	t_AST_NODE	*node;

	node = malloc(sizeof(t_AST_NODE));
	if (!node)
		return (NULL);
	node->op = NOT_REDIR;
	node->type = WORD;
	node->text = new_str(text);
	node->expansions = expansions;
	return (node);
}

t_AST_NODE	*new_ast_redirect(
	const char *text, t_AST_expansion *expansions[], t_redirect_op op)
{
	t_AST_NODE	*node;

	node = new_ast_word(text, expansions);
	if (!node)
		return (NULL);
	node->op = op;
	node->type = REDIRECT;
	return (node);
}

t_AST_COMMAND	*new_ast_command(
	t_AST_NODE *name, t_AST_NODE *prefixes[], t_AST_NODE *suffixes[])
{
	t_AST_COMMAND	*new;

	new = malloc(sizeof(t_AST_COMMAND));
	if (!new)
		return (NULL);
	new->name = name;
	new->prefixes = prefixes;
	new->suffixes = suffixes;
	return (new);
}
