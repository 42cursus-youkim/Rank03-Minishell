/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_AST_type	tokentype_check(t_scan_node *node)
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
