#include "minishell.h"

static int	check_args(t_context *context)
{
	int			arg_idx;
	const int	argv_len = ft_arr_len(context->argv);

	if (argv_len == 1)
		return (EXIT_SUCCESS);
	arg_idx = 0;
	while (++arg_idx < argv_len)
	{
		if (!is_str_digit(context->argv[arg_idx]))
		{
			error_msg_return((char *[]){"exit: ", context->argv[arg_idx],
				": numeric argument required", NULL});
			return (EXIT_EXIT_STATUS_OUT_OF_RANGE);
		}
		else if (argv_len > 2)
		{
			error_msg_category("exit", "too many arguments");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

//	FIXME: needs to work in pipe too
int	builtin_exit(t_context *context, t_shell *shell)
{
	int			exitcode;
	int			exitcode_input;

	exitcode = check_args(context);
	if (exitcode == EXIT_EXIT_STATUS_OUT_OF_RANGE)
		;
	else if (exitcode == EXIT_FAILURE)
		return (exitcode);
	else if (check_no_opt(context->argv, "exit") != OK)
		exitcode = EXIT_EXIT_STATUS_OUT_OF_RANGE;
	else if (ft_atoi(context->argv[1], &exitcode_input) == OK)
		exitcode = exitcode_input % EXIT_CODE_RANGE;
	else
		exitcode = shell->env->exitcode;
	del_context(context);
	api_exit(shell, exitcode);
	return (EXIT_FAILURE);
}
