#include "libft.h"

t_res	error_msg_category(char *category, char *msg)
{
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED, category, ": ", msg, END "\n", NULL});
	return (ERR);
}

t_res	error_syscall(char *category)
{
	return (error_msg_category(category, strerror(errno)));
}
