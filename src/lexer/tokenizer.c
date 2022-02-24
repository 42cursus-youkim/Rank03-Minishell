#include "minishell.h"

t_res	quotes_remove_loop(char **new, char *last_quote, bool *open, char c)
{
	if (!*open && is_quotechar(c))
	{
		*open = true;
		*last_quote = c;
		return (OK);
	}
	if (*open && *last_quote == c)
	{
		*open = false;
		return (OK);
	}
	if (ft_str_append(new, c) == ERR)
		return (free_n_return(new, error_msg_return(MALLOC_ERROR_MSG)));
	return (OK);
}

char	*new_quotes_remove(const char *str)
{
	char	*new;
	int		i;
	char	last_quote;
	bool	open;

	new = new_str("");
	if (!new)
		return (NULL);
	open = false;
	i = -1;
	while (str[++i])
	{
		if (quotes_remove_loop(&new, &last_quote, &open, str[i]) == ERR)
			return (NULL);
	}
	return (new);
}

t_res	node_tokenize(t_token *tokens[], t_scan_node *node, int i)
{
	if (!node->expansions)
		(*tokens)[i].text = new_quotes_remove(node->text);
	else
		(*tokens)[i].text = new_str(node->text);
	if (!(*tokens)[i].text)
		return (error_msg_return(MALLOC_ERROR_MSG));
	(*tokens)[i].expansions = new_ast_expansions(node->expansions);
	if (!(*tokens)[i].expansions)
		return (error_msg_return(MALLOC_ERROR_MSG));
	return (OK);
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
		if (node_tokenize(&tokens, node, i) == ERR)
		{
			del_list(&scan_list, del_scan_node);
			del_tokens(tokens);
			return (NULL);
		}
		current = current->next;
	}
	del_list(&scan_list, del_scan_node);
	return (tokens);
}
