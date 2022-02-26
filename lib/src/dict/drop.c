#include "libft.h"

t_res	dict_drop(t_dict *dict, char *key)
{
	int			i;
	const int	id = dict_getid(dict->capacity, key);

	if (dict_get(dict, key) == NULL)
		return (ERR);
	i = id - 1;
	while (++i < dict->capacity)
		if (is_key_update(dict, i, key))
			return (del_ditem(dict, i));
	i = 0;
	while (++i < id)
		if (is_key_update(dict, i, key))
			return (del_ditem(dict, i));
	return (ERR);
}
