#include "minishell.h"

static t_AST_type	tokentype_check(t_scan_node *node)
{
	const char	*str = node->text;

	if (is_str_equal(str, "|"))
		return (PIPELINE);
	if (is_str_equal(str, "<") || is_str_equal(str, "<<")
		|| is_str_equal(str, ">") || is_str_equal(str, ">>"))
		return (REDIRECT);
	return (WORD);
}

void	tokens_print(t_token tokens[])
{
	int			i;
	const char	*type_str[] = {
		BWHT "💬 WORD", BBLU "🔗 PIPELINE",
		BYEL "🔁 REDIRECT", BRED "🔥 COMMAND"};

	i = -1;
	while (tokens[++i].text)
	{
		printf("[%2d] %-12s" BGRN "\t%s\n" END,
			i, type_str[tokens[i].type], tokens[i].text);
		if (tokens[i].expansions)
			expansions_print(tokens[i].expansions);
	}
}

void	del_tokens(t_token tokens[])
{
	int	i;

	i = -1;
	while (tokens[++i].text)
	{
		free(tokens[i].text);
		del_ast_expansions(tokens[i].expansions);
	}
	free(tokens);
}

char	*new_quotes_remove(const char *str)
{
	char	*new;
	int		i;
	char	last_quote;
	bool	open;

	new = new_str("");
	open = false;
	i = -1;
	while (str[++i])
	{
		if (!open && is_quotechar(str[i]))
		{
			open = true;
			last_quote = str[i];
			continue ;
		}
		if (open && last_quote == str[i])
		{
			open = false;
			continue ;
		}
		ft_str_append(&new, str[i]);
	}
	return (new);
}

t_token	*tokenizer(t_list *scan_list)
{
	t_token			*tokens;
	const int		len = ft_list_size(scan_list);
	int				i;
	t_list			*current;
	t_scan_node		*node;

	tokens = ft_calloc(sizeof(t_token), len);
	if (!tokens)
		return (NULL);
	current = scan_list;
	i = -1;
	while (++i < len)
	{
		node = (t_scan_node *)current->content;
		tokens[i].type = tokentype_check(node);
		if (!node->expansions)
			tokens[i].text = new_quotes_remove(node->text);
		else
			tokens[i].text = new_str(node->text);
		tokens[i].expansions = new_ast_expansions(node->expansions);
		current = current->next;
	}
	del_list(&scan_list, del_scan_node);
	return (tokens);
}
