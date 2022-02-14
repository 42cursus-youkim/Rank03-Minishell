#include "libft.h"

//	visualize list. only works when EVERY values are string.
void	dict_print(t_dict *dict)
{
	int			id;
	t_ditem		*item;

	id = -1;
	printf(UMAG "ID |%-8s|%-6s(%d/%d)\n" END,
		"KEY", "VALUE", dict->size, dict->capacity);
	while (++id < dict->capacity)
	{
		item = dict->items[id];
		if (item && item->key)
			printf(HYEL "%2d |%-8s|" HGRN "%s\n" END,
				id, item->key, item->value);
		else
			printf("%2d |%8s|\n", id, "");
	}
}
