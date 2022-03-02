/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_scan_node	*new_scan_node(char *str, t_AST_expansion **arr)
{
	t_scan_node	*new;

	new = ft_calloc(sizeof(t_scan_node), 0);
	new->text = str;
	new->expansions = arr;
	return (new);
}

void	del_scan_node(void *param)
{
	t_scan_node	*node;

	node = (t_scan_node *)param;
	free(node->text);
	if (node->expansions)
		del_ast_expansions(node->expansions);
	free(node);
}

void	scan_node_print(void *param)
{
	t_scan_node	*node;

	node = (t_scan_node *)param;
	printf("\"" HGRN "%s" END "\"\n", node->text);
	if (node->expansions)
		expansions_print(node->expansions);
}
