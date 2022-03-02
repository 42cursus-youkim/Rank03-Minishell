/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*new_list(void *content)
{
	t_list	*new_list;

	new_list = ft_calloc(sizeof(t_list), 0);
	if (new_list == NULL)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

int	ft_list_size(t_list *list)
{
	t_list	*current;
	int		size;

	current = list;
	size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void	ft_list_append(t_list **list, t_list *new_node)
{
	t_list	*current;

	current = *list;
	if (*list == NULL)
		*list = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	del_list(t_list **list, t_del_f del)
{
	t_list	*current;

	while (*list != NULL)
	{
		current = *list;
		*list = (*list)->next;
		del(current->content);
		free(current);
	}
	*list = NULL;
}

void	ft_list_print(t_list *list, t_print_f print_func)
{
	t_list		*current;
	int			i;
	const int	len = ft_list_size(list);
	const int	pad = ft_digit_len(len - 1);

	current = list;
	i = 0;
	while (current != NULL)
	{
		printf(BHYEL "[%*d] " END, pad, i++);
		print_func(current->content);
		current = current->next;
	}
}
