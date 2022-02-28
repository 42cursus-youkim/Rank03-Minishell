#include "libft.h"

//	creates a new dictonary item, with key and value
t_ditem	*new_ditem(const char *key, void *value)
{
	t_ditem	*item;

	item = ft_calloc(sizeof(t_ditem), 0);
	item->key = new_str(key);
	item->value = value;
	item->order = ERR;
	return (item);
}

//	creates new NULL-set array of items
t_ditem	**new_ditem_arr(int capacity)
{
	t_ditem	**items;

	items = ft_calloc(sizeof(t_ditem *), capacity);
	return (items);
}

t_ditem	**new_dict_kv_ordered(t_dict *dict)
{
	int		id;
	t_ditem	*item;
	t_ditem	**items;

	items = new_ditem_arr(dict->size);
	id = -1;
	while (++id < dict->capacity)
	{
		item = dict->items[id];
		if (!item || !item->key)
			continue ;
		items[item->order] = item;
	}
	return (items);
}
