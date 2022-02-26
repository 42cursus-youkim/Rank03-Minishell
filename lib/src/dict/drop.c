#include "libft.h"

void	dict_drop(t_dict *dict, char *key)
{
	int			i;
	const int	id = dict_getid(dict->capacity, key);

	i = id - 1;
	while (++i < dict->capacity)
		if (is_key_update(dict, i, key))
			return (del_ditem(dict, i));
	i = 0;
	while (++i < id)
		if (is_key_update(dict, i, key))
			return (del_ditem(dict, i));
}

