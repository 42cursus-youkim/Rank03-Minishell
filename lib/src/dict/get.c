#include "libft.h"

//	wrapper for hash that returns index got from hash
int	dict_getid(int capacity, char *key)
{
	return (hash_fnv1a(key) % (uint64_t)capacity);
}

static bool	does_itemmatch(t_ditem *item, char *key)
{
	return (item && item->key && is_str_equal(item->key, key));
}

//	finds value by key, return NULL is not found
void	*dict_get(t_dict *dict, char *key)
{
	int		i;
	int		id;

	id = dict_getid(dict->capacity, key);
	i = id - 1;
	while (++i < dict->capacity)
		if (does_itemmatch(dict->items[i], key))
			return (dict->items[i]->value);
	i = -1;
	while (++i < id)
		if (does_itemmatch(dict->items[i], key))
			return (dict->items[i]->value);
	return (NULL);
}

//	finds value by key, return default value if not found
char	*dict_get_default(t_dict *dict, char *key, char *default_value)
{
	char	*value;

	value = dict_get(dict, key);
	if (!value)
		return (default_value);
	return (value);
}
