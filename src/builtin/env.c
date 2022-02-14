#include "minishell.h"

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

t_dict	*new_env(char *envp[])
{
	int		i;
	t_dict	*env;

	i = -1;
	env = new_dict(free);
	while (envp[++i])
		env_set(env, envp[i]);
	return (env);
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
		printf(BHYEL "%-s" END "=" HGRN "%s\n" END, item->key, item->value);
	}
	free(items);
}

char	**new_arr_env(t_dict *env)
{
	int		i;
	t_ditem	*item;
	char	**envp;

	envp = ft_calloc(sizeof(char *), env->size);
	if (!envp)
		return (NULL);
	i = -1;
	while (++i < env->capacity)
	{
		item = env->items[i];
		if (!item)
			continue ;
		envp[item->order] = new_str_join((char *[]){
				item->key, item->value, NULL}, '=');
	}
	return (envp);
}
