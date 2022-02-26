#include "minishell.h"

void	builtin_cd(t_context *context, t_shell *shell)
{
	if (ft_arr_len(context->argv) != 1 + 1)
	{
		ft_write(STDERR_FILENO, RED "cd: too many arguments\n" END);
		return ;
	}
	if (chdir(context->argv[1]) == ERR)
		error_syscall("cd");
	dict_set(shell->env, "PWD", getcwd(NULL, 0));
}
