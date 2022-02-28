#include "minishell.h"

static bool	is_opt_nonewline_valid(char *str, bool *is_newline_p)
{
	int	i;

	if (!is_opt(str))
		return (false);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (false);
	*is_newline_p = false;
	return (true);
}

static void	echo_inner(int i, int len, char *str)
{
	ft_write(STDOUT_FILENO, str);
	if (i != len)
		ft_write(STDOUT_FILENO, " ");
}

int	builtin_echo(t_context *context, t_shell *shell)
{
	int			i;
	const int	len = ft_arr_len(context->argv) - 1;
	bool		is_newline;
	bool		is_listen_opt;

	(void)shell;
	is_newline = true;
	is_listen_opt = true;
	if (len == ERR)
		return (EXIT_FAILURE);
	i = 0;
	while (++i <= len && is_listen_opt)
	{
		is_listen_opt = is_opt_nonewline_valid(context->argv[i], &is_newline);
		if (!is_listen_opt)
			echo_inner(i, len, context->argv[i]);
	}
	--i;
	while (++i <= len)
		echo_inner(i, len, context->argv[i]);
	if (is_newline)
		ft_write(STDOUT_FILENO, "\n");
	return (EXIT_SUCCESS);
}
