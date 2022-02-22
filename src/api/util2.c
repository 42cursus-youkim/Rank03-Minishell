#include "minishell.h"

bool	is_file_exists(char *filename)
{
	struct stat	buffer;

	return (stat(filename, &buffer) == OK);
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
