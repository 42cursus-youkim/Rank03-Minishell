/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_set_exitcode(t_dict *env, int exitcode)
{
	env->exitcode = exitcode;
	ft_str_replace(&env->exitcode_str, new_itoa(exitcode));
}

static bool	is_key_valid(char *key)
{
	int	i;

	i = 0;
	if (!is_1stchar_valid(key[i]) || key[i] == '{')
		return (false);
	while (key[++i])
	{
		if (!is_variable_char_valid(key[i]))
			return (false);
	}
	return (true);
}

/*	if only key is passed: save NULL
	if key and value are passed: save key=value
*/
t_res	env_set(t_dict *env, char *str)
{
	int		eq_idx;
	char	*key;
	char	*value;

	eq_idx = ft_strchr_i(str, '=');
	if (eq_idx == ERR)
		return (dict_set(env, str, NULL));
	key = new_str_slice(str, 0, eq_idx);
	if (!is_key_valid(key))
	{
		error_msg_return((char *[]){"export: ",
			"`", str, "': not a valid identifier", NULL});
		return (free_n_return(key, ERR));
	}
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
