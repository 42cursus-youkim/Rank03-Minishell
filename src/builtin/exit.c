#include "minishell.h"

//	only works
int	builtin_exit(t_context *context, t_shell *shell)
{
	int			exitcode_input;
	const int	argv_len = ft_arr_len(context->argv);

	if (argv_len > 2)
	{
		error_msg_category("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	else if (check_no_opt(context->argv, "exit") != OK)
		api_exit(shell, EXIT_EXIT_STATUS_OUT_OF_RANGE);
	else if (ft_atoi(context->argv[1], &exitcode_input) == OK)
		api_exit(shell, exitcode_input % EXIT_CODE_RANGE);
	else
		api_exit(shell, shell->env->exitcode);
	return (EXIT_FAILURE);
}
