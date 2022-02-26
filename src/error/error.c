#include "minishell.h"

//	FIXME: use ft_writes internally
t_res	error_msg_return(char *message[])
{
	const int	len = ft_arr_len(message);
	int			i;

	i = -1;
	while (++i < len)
		printf("%s", message[i]);
	return (ERR);
}

t_res	error_malloc_msg(void)
{
	return (error_msg_return(
		(char *[]){BRED, MINISHELL, MALLOC_ERROR, END, NULL}));
}

t_res	error_with_exitcode(char *message[], t_dict *env, int exitcode)
{
	env_set_exitcode(env, exitcode);
	return (error_msg_return(message));
}