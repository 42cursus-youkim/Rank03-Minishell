#include "minishell.h"

char	**new_path(t_dict *env)
{
	const char	*pathstr = dict_get(env, "PATH");
	char		**path;
	// char		*temp;
	int			i;

	path = new_str_split(pathstr, ':');
	i = -1;
	// while (path[++i])
	// {
	// 	if (path[i][0] == '~')
	// 	{
	// 		temp =
	// 		path[i] = new_str_join((char *[]){
	// 			dict_get(env, "HOME"), temp, NULL}, '\0');
	// 	}
	// }
	return (path);
}

void	path_print(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		printf(GRN "%s\n" END, path[i]);
}
