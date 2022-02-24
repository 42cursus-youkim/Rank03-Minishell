#include "minishell.h"

t_res	error_msg_return(char *message[])
{
	const int	len = ft_arr_len(message);
	int			i;

	i = -1;
	while (++i < len)
		printf("%s", message[i]);
	return (ERR);
}