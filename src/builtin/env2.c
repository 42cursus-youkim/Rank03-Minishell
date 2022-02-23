#include "minishell.h"

void	env_set_exitcode(t_dict *env, int exitcode)
{
	ft_str_replace(&env->exitcode_str, new_itoa(exitcode));
}

void	env_set(t_dict *env, char *str)
{
	int		eq_idx;
	char	*key;
	char	*value;

	eq_idx = ft_strchr_i(str, '=');
	key = new_str_slice(str, 0, eq_idx);
	value = new_str_slice(str, eq_idx + 1, ft_strlen(str));
	dict_set(env, key, value);
	free(key);
}

char	*env_get(t_dict *env, char *key)
{
	if (is_str_equal(key, "?"))
		return (env->exitcode_str);
	return (dict_get_default(env, key, ""));
}


void	env_print(t_dict *env)
{
	int		id;
	t_ditem	*item;
	t_ditem	**items;

	items = new_dict_kv_ordered(env);
	if (!items)
		return ;
	id = -1;
	while (++id < env->size)
	{
		item = items[id];
		printf(BHYEL "%-s" END "=" HGRN "%s\n" END,
			item->key, (char *)item->value);
	}
	free(items);
}