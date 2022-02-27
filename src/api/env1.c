#include "minishell.h"

t_dict	*new_env(char *envp[])
{
	int		i;
	t_dict	*env;

	env = new_dict(free);
	if (!env)
		return (NULL);
	env->exitcode = EXIT_SUCCESS;
	env->exitcode_str = new_itoa(EXIT_SUCCESS);
	i = -1;
	while (envp[++i])
		env_set(env, envp[i]);
	return (env);
}

void	del_env(t_dict *env)
{
	free(env->exitcode_str);
	del_dict(env);
}

char	**new_env_to_envp(t_dict *env)
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
		if (!item || !item->key || !item->value)
			continue ;
		printf(BHYEL "%-s" END "=" HGRN "%s\n" END,
			item->key, (char *)item->value);
	}
	free(items);
}
