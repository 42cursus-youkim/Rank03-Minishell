#include "minishell.h"

t_AST_NODE	*new_ast_word(
	const char *text, t_AST_expansion **expansions)
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
	const char *text, t_AST_expansion **expansions, t_redirect_op op)
{
	t_AST_NODE	*node;

	node = new_ast_word(text, expansions);
	if (!node)
		return (NULL);
	node->type = REDIRECT;
	node->op = op;
	return (node);
}


t_AST_COMMAND	*new_ast_command(
	t_AST_NODE *name, t_AST_NODE **prefixes, t_AST_NODE **suffixes)
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
