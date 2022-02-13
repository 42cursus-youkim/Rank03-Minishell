#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;


	t_dict *env = new_env(envp);
	env_print(env);
	char **new_envp = new_env_to_envp(env);
	for (int i = 0; new_envp[i]; i++)
		printf("%s\n", new_envp[i]);
	// t_dict *env = new_env(envp);
	// char **path = new_path(env);
	// path_print(path);
	// del_arr(path);
	// env_print(env);
	// del_dict(env);
	// dict_print(dict);
	// printf("PWD is %s\n", dict_get(dict, "PWD"));
	// del_dict(dict);
	return (0);

}