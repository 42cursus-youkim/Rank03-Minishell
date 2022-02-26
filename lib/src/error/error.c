#include "libft.h"

//	FIXME: use ft_writes internally
t_res	error_msg_return(char *message[])
{
	const int	len = ft_arr_len(message);
	int			i;

	i = -1;
	while (++i < len)
		ft_write(STDERR_FILENO, message[i]);
	return (ERR);
}

t_res	error_malloc_msg(void)
{
	return (error_msg_return(
			(char *[]){BRED, MINISHELL, MALLOC_ERROR, END, NULL}));
}

void	error_syscall(char *category)
{
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED, category, ": ", strerror(errno), END "\n", NULL});
}
