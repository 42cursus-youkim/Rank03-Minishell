#include "minishell.h"

int	main(int argc, char *argv[], char *envp[]) {
	(void)argc;
	(void)argv;
	(void)envp;
	t_dict *dict = new_dict(no_free);

	dict_set(dict, "PATH", "/bin:/usr/bin");
	dict_set(dict, "HOME", "/home/");
	dict_set(dict, "PWD", "/home/");
	dict_print(dict);
	del_dict(dict);
	return (0);
}
