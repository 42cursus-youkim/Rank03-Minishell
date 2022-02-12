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
	int		i;

	i = -1;
	while (++i < env->capacity)
		if (env->items[i])
			printf(BHYEL "%s" END "=" GRN "%s\n" END,
				env->items[i]->key, env->items[i]->value);
}
