/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef void	(*t_print_f)(void *param);

//@func
/*
** < list.c > */

t_list	*new_list(void *content);
int		ft_list_size(t_list *list);
void	ft_list_append(t_list **list, t_list *new_node);
void	del_list(t_list **list, t_del_f del);
void	ft_list_print(t_list *list, t_print_f print_func);
#endif