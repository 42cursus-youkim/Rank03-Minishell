#include "minishell.h"

void	builtin_cd(t_context *context, t_shell *shell)
{
	if (ft_arr_len(context->argv) != 1 + 1)
	{
		printf(RED "cd: too many arguments\n" END);
		return ;
	}
	//	TODO: check path is valid
	printf("new pwd: %s\n", context->argv[1]);
	if (chdir(context->argv[1]) == ERR)
		error_syscall("cd");
	dict_set(shell->env, "PWD", getcwd(NULL, 0));
}
