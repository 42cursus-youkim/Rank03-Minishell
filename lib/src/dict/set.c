#include "libft.h"

//	insert new item at empty index of dictionary
static void	dict_insert(t_dict *dict, int id, char *key, void *value)
{
	t_ditem	*item;

	item = new_ditem(key, value);
	item->order = dict->size;
	dict->items[id] = item;
	dict->size++;
}

//	replace the value of an existing key
static void	dict_update(t_dict *dict, int id, void *value)
{
	dict->del_value(dict->items[id]->value);
	dict->items[id]->value = value;
}

//	probe around empty index to insert new item
static void	dict_probe(t_dict *dict, int id, char *key, void *value)
{
	int	i;

	i = id;
	while (++i < dict->capacity)
		if (is_key_vacant(dict, i))
			return (dict_insert(dict, i, key, value));
	i = 0;
	while (i < id)
		if (is_key_vacant(dict, i++))
			return (dict_insert(dict, --i, key, value));
	printf(BRED "dict is full, probe failed" END);
}

/*	all values provided are MOVED and NOT COPIED!
	insert NULL for destructor if you wish to use constants for values
	key vacant: inserts new item
	key same  : replaces value
	key diff  : probe for empty index
*/
t_res	dict_set(t_dict *dict, char *key, void *value)
{
	int	id;

	if (!is_input_valid(dict, key, value))
		return (ERR);
	if (is_dict_almostfull(dict))
		if (dict_expand(dict) == ERR)
			return (ERR);
	id = dict_getid(dict->capacity, key);
	if (is_key_vacant(dict, id))
		dict_insert(dict, id, key, value);
	else if (is_key_update(dict, id, key))
		dict_update(dict, id, value);
	else
		dict_probe(dict, id, key, value);
	return (OK);
}
