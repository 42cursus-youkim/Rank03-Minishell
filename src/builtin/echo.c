#include "minishell.h"

void	builtin_echo(t_context *context)
{
	int			i;
	const int	len = ft_arr_len(context->argv) - 1;
	// bool	is_newline;

	if (len == ERR)
		return ;
	i = 0;
	while (++i <= len)
	{
		ft_write(STDOUT_FILENO, context->argv[i]);
		if (i != len)
			ft_write(STDOUT_FILENO, " ");
	}
	ft_write(STDOUT_FILENO, "\n");
}
