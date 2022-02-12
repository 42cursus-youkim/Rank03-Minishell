#include "libft.h"

//	does nothing, for placeholder destructor
void	no_free(void *data)
{
	(void)data;
}

void	del_ditem(t_dict *dict, int id)
{
	t_ditem	*item;

	item = dict->items[id];
	free(item->key);
	dict->del_value(item->value);
	free(item);
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
