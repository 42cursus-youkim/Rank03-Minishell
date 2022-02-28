#include "minishell.h"

bool	is_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == ERR)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

bool	is_file_exists(char *path)
{
	struct stat	buffer;

	return (stat(path, &buffer) == OK);
}

bool	is_executable_exists(char *file, t_dict *env)
{
	int		i;
	char	**names;
	bool	result;

	if (is_file_exists(file))
		return (true);
	names = new_names_from_path(file, env);
	i = -1;
	result = false;
	while (names[++i])
		if (is_file_exists(names[i]))
			result = true;
	del_arr(names);
	return (result);
}

char	*new_executable_from_env(char *file, t_dict *env)
{
	int		i;
	char	**path;
	char	*executable;

	if (is_file_exists(file) && is_executable_exists(file, env))
	{
		error_msg_category("is a directory", file);
		return (NULL);
	}
	else if (is_file_exists(file))
		return (new_str(file));
	else if (!is_executable_exists(file, env))
		return (NULL);
	path = new_names_from_path(file, env);
	i = -1;
	while (path[++i])
		if (is_file_exists(path[i]))
			break ;
	executable = new_str(path[i]);
	del_arr(path);
	return (executable);
}
