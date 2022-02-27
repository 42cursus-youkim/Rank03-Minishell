#include "libft.h"

static	t_res	del_ditem_value(t_dict *dict, int id)
{
	t_ditem	*item;

	item = dict->items[id];
	if (!item || !item->value)
		return (ERR);
	dict->del_value(item->value);
	item->value = NULL;
	return (OK);
}

t_res	dict_drop(t_dict *dict, char *key)
{
	int			i;
	const int	id = dict_getid(dict->capacity, key);

	if (dict_get(dict, key) == NULL)
		return (ERR);
	i = id - 1;
	while (++i < dict->capacity)
		if (is_key_update(dict, i, key))
			return (del_ditem_value(dict, i));
	i = 0;
	while (++i < id)
		if (is_key_update(dict, i, key))
			return (del_ditem_value(dict, i));
	return (ERR);
}
