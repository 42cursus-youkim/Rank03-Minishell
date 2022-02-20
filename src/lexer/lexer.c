#include "minishell.h"

static char	*new_quotes_remove(const char *str)
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

t_token	*lexer(char *line)
{
	t_list	*scan_list;
	t_token	*tokens;

	scan_list = NULL;
	tokens = NULL;
	if (scanner(&scan_list, line) == ERR)
		del_list(&scan_list, del_scan_node);
	else
		tokens = tokenizer(scan_list);
	return (tokens);
}
