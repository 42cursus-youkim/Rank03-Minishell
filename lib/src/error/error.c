#include "libft.h"

void	error_msg_category(char *category, char *msg)
{
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED, category, ": ", msg, END "\n", NULL});
}

void	error_syscall(char *category)
{
	error_msg_category(category, strerror(errno));
}
