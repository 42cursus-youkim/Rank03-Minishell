#include "minishell.h"

bool	is_path_tilde_expansion(char *path)
{
	const int	len = ft_strlen(path);

	if (!is_str_first(path, '~'))
		return (false);
	return ((len == 1) || (len >= 2 && path[1] == '/'));
}

t_res	path_replace_tilde(char **path_p, t_dict *env)
{
	if (!is_path_tilde_expansion(*path_p))
		return (ERR);
	ft_str_replace(path_p, new_str_join((char *[]){
			env_get(env, "HOME"), *path_p + 1, NULL}, '\0'));
	return (OK);
}
