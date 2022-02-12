#include "libft.h"

//	creates a new dictonary item, with key and value
t_ditem	*new_ditem(const char *key, void *value)
{
	t_ditem	*item;

	item = malloc(sizeof(t_ditem));
	item->key = new_str(key);
	item->value = value;
	return (item);
}

//	creates new NULL-set array of items
t_ditem	**new_ditem_arr(int capacity)
{
	int		id;
	t_ditem	**items;

	items = malloc(capacity * sizeof(t_ditem *));
	if (!items)
		return (NULL);
	id = -1;
	while (++id < capacity)
		items[id] = NULL;
	return (items);
}

//	initializes dictionary, NULLs items, saves
static void	dict_init(t_dict *dict, t_del_f del_value)
{
	dict->size = 0;
	dict->capacity = DICT_INITIAL_CAPACITY;
	dict->items = new_ditem_arr(dict->capacity);
	if (del_value)
		dict->del_value = del_value;
	else
		dict->del_value = no_free;
}

/*	creates an empty dict with destructor (ex: free).
	pass NULL for constant values.
	Internal structure assumes all items are of SAME TYPE.
	(at least they could be freed with same destructor)
*/
t_dict	*new_dict(t_del_f del_value)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	dict_init(dict, del_value);
	if (dict->items)
		return (dict);
	else
	{
		free(dict->items);
		free(dict);
		return (NULL);
	}
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
