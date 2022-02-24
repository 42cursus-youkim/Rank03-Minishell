#include "libft.h"

int	ft_write(int fd, const char *str)
{
	return (write(fd, str, ft_strlen(str)));
}

//	write multiple strings
int	ft_writes(int fd, char *arr[])
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (arr[++i])
		res += ft_write(fd, arr[i]);
	return (res);
}
