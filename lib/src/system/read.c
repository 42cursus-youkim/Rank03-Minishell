#include "libft.h"

/*	similar to read but NULL-terminates the string. returns sizes read.
	string size should be at least 1 bigger than the buffer_size.
*/
int	ft_read(int fd, char *buf, int buffer_size)
{
	int	len;

	ft_bzero(buf, buffer_size + 1);
	len = read(fd, buf, buffer_size);
	return (len);
}
