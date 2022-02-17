#include "minishell.h"

char	*new_path_resolved(char *path, t_dict *env)
{
	char	*new;

	new = new_str(path);
	if (path[0] == '~')
		ft_str_replace(&new, new_str_join((char *[]){
			env_get(env, "HOME"), path + 1, NULL}, '\0'));
	if (path[ft_strlen(path) - 1] != '/')
		ft_str_replace(&new, new_str_join((char *[]){
			new, "/", NULL}, '\0'));
	return (new);
}

char	**new_raw_path(t_dict *env)
{
	const char	*pathstr = dict_get(env, "PATH");

	if (!pathstr)
		return (NULL);
	return (new_str_split(pathstr, ':'));
}

char	**new_path(t_dict *env)
{
	int		i;
	char	**raw;
	char	**path;

	raw = new_raw_path(env);
	path = new_arr(NULL);
	i = -1;
	while (raw[++i])
		ft_arr_append_free(&path, new_path_resolved(raw[i], env));
	return (path);
}

