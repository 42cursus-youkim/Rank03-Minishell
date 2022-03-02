/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	does nothing, for placeholder destructor
void	no_free(void *data)
{
	(void)data;
}

t_res	del_ditem(t_dict *dict, int id)
{
	t_ditem	*item;

	item = dict->items[id];
	if (!item)
		return (ERR);
	free(item->key);
	dict->del_value(item->value);
	free(item);
	dict->items[id] = NULL;
	return (OK);
}

//	uses internal function pointer as destructor.
void	del_dict(t_dict *dict)
{
	int	id;

	if (!dict)
		return ;
	id = -1;
	while (++id < dict->capacity)
		if (dict->items[id])
			del_ditem(dict, id);
	free(dict->items);
	free(dict);
}
