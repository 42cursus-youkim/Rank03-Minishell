#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_dict	*env;

	(void)argc;
	(void)argv;
	env = new_env(envp);
	prompt(env);
	del_dict(env);
	return (0);
}
