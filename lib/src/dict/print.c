#include "libft.h"

static void	pad_init(t_dict *dict, t_dpad pad[2], int size)
{
	int		id;
	t_ditem	*item;

	pad[PAD_SIZE] = ft_digit_len(size - 1);
	pad[PAD_KEY] = 0;
	if (!dict || dict->size == 0)
		return ;
	id = -1;
	while (++id < dict->capacity)
	{
		item = dict->items[id];
		if (!item || !item->key)
			continue ;
		pad[PAD_KEY] = ft_max(pad[PAD_KEY], ft_strlen(item->key));
	}
}

//	visualize list. only works when EVERY values are string.
void	dict_print(t_dict *dict)
{
	int		id;
	t_dpad	pad[2];
	t_ditem	*item;

	pad_init(dict, pad, dict->capacity);
	printf(UMAG "%*s |%-*s|%-6s(%d/%d)\n" END,
		pad[PAD_SIZE], "ID", pad[PAD_KEY], "KEY", "VALUE",
		dict->size, dict->capacity);
	id = -1;
	while (++id < dict->capacity)
	{
		item = dict->items[id];
		if (item && item->key)
			printf(HYEL "%*d |%-*s|" HGRN "%s\n" END,
				pad[PAD_SIZE], id, pad[PAD_KEY], item->key, item->value);
		else
			printf("%*d |%*s|\n", pad[PAD_SIZE], id, pad[PAD_KEY], "");
	}
}

static t_ditem	**new_kv_ordered(t_dict *dict)
{
	int		id;
	t_ditem	*item;
	t_ditem	**items;

	items = new_ditem_arr(dict->size);
	if (!items)
		return (NULL);
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

//	visualize list with order. only works when EVERY values are string.
void	dict_print_ordered(t_dict *dict)
{
	int		id;
	t_dpad	pad[2];
	t_ditem	*item;
	t_ditem	**items;

	pad_init(dict, pad, dict->size);
	pad[PAD_SIZE] = ft_max(5, pad[PAD_SIZE]);
	items = new_kv_ordered(dict);
	if (!items)
		return ;
	printf(UMAG "%*s |%-*s|%-6s(x%d)\n" END,
		pad[PAD_SIZE], "ORDER", pad[PAD_KEY], "KEY", "VALUE", dict->capacity);
	id = -1;
	while (++id < dict->size)
	{
		item = items[id];
		printf(HYEL "%*d |%-*s|" HGRN "%s\n" END,
			pad[PAD_SIZE], id, pad[PAD_KEY], item->key, item->value);
	}
	free(items);
}
