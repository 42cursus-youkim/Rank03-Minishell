#include "minishell.h"

void	env_set_exitcode(t_dict *env, int exitcode)
{
	env->exitcode = exitcode;
	ft_str_replace(&env->exitcode_str, new_itoa(exitcode));
}

t_res	env_set(t_dict *env, char *str)
{
	int		eq_idx;
	char	*key;
	char	*value;

	eq_idx = ft_strchr_i(str, '=');
	if (eq_idx == ERR)
		return (error_msg_category("env",
				"exporting variable without value not supported"));
	key = new_str_slice(str, 0, eq_idx);
	value = new_str_slice(str, eq_idx + 1, ft_strlen(str));
	dict_set(env, key, value);
	free(key);
	return (OK);
}

char	*env_get(t_dict *env, char *key)
{
	if (is_str_equal(key, "?"))
		return (env->exitcode_str);
	return (dict_get_default(env, key, ""));
}

