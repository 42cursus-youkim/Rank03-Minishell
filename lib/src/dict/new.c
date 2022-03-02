/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	initializes dictionary, NULLs items, saves
static t_res	dict_init(t_dict *dict, t_del_f del_value)
{
	dict->size = 0;
	dict->capacity = DICT_INITIAL_CAPACITY;
	dict->items = new_ditem_arr(dict->capacity);
	if (!dict->items)
		return (ERR);
	if (del_value)
		dict->del_value = del_value;
	else
		dict->del_value = no_free;
	return (OK);
}

/*	creates an empty dict with destructor (ex: free).
	pass NULL for constant values.
	Internal structure assumes all items are of SAME TYPE.
	(at least they could be freed with same destructor)
*/
t_dict	*new_dict(t_del_f del_value)
{
	t_dict	*dict;

	dict = ft_calloc(sizeof(t_dict), 0);
	if (!dict)
		return (NULL);
	if (dict_init(dict, del_value) == ERR)
	{
		free(dict);
		return (NULL);
	}
	return (dict);
}

//	creates a new dict with allocated string k,v
t_dict	*new_dict_str(char *key[], char *value[])
{
	int		i;
	t_dict	*dict;

	dict = new_dict(NULL);
	if (!dict)
		return (NULL);
	i = -1;
	while (key[++i] && value[i])
		dict_set(dict, key[i], value[i]);
	return (dict);
}
