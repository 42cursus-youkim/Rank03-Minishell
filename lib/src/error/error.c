#include "libft.h"

t_res	error_syscall(char *category)
{
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED "minishell: ", category, ": ", strerror(errno), END "\n", NULL});
	return (ERR);
}
