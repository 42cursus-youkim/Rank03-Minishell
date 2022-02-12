#include "libft.h"

bool	is_input_valid(const t_dict *dict, const char *key, const void *value)
{
	return (dict && key && value);
}

bool	is_key_vacant(const t_dict *dict, int id)
{
	return (!dict->items[id]);
}

bool	is_key_update(const t_dict *dict, int id, const char *key)
{
	return (is_str_equal(dict->items[id]->key, key));
}

bool	is_dict_almostfull(const t_dict *dict)
{
	return (dict->size >= dict->capacity / 2);
}

bool	is_capacity_overflow(const t_dict *dict)
{
	return (dict->capacity * 2 < dict->capacity);
}