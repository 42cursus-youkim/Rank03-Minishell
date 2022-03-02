/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_res	quotes_remove_loop(
	char **new, char *last_quote, bool *open, char c)
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
	ft_str_append(new, c);
	return (OK);
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
		quotes_remove_loop(&new, &last_quote, &open, str[i]);
	return (new);
}

t_token	*new_tokens_from_list(t_list *scan_list)
{
	t_token			*tokens;
	const int		len = ft_list_size(scan_list);
	int				i;
	t_list			*current;
	t_scan_node		*node;

	tokens = ft_calloc(sizeof(t_token), len);
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
