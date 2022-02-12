#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	t_dict *env = new_env(envp);
	char **path = new_path(env);
	path_print(path);
	del_dict(env);
	del_arr(path);
	// printf("key is %s, value is %s\n", key, value);

	// dict_set(dict, "PATH", "/bin:/usr/bin");
	// dict_set(dict, "HOME", "/home/");
	// dict_set(dict, "PWD", "/home/");
	// dict_print(dict);
	// printf("PWD is %s\n", dict_get(dict, "PWD"));
	// del_dict(dict);
	return (0);

}