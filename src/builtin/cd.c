#include "minishell.h"

void	builtin_cd(t_context *context, t_shell *shell)
{
	if (ft_arr_len(context->argv) != 1 + 1)
	{
		error_msg_category("cd", "too many arguments");
		return ;
	}
	if (chdir(context->argv[1]) == ERR)
		error_syscall("cd");
	dict_set(shell->env, "PWD", getcwd(NULL, 0));
}
