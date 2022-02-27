#include "libft.h"

/*	similar to read but NULL-terminates the string. returns sizes read.
	string size should be at least 1 bigger than the buffer_size.
*/
int	ft_read(int fd, char *buf, int buffer_size)
{
	int	len;

	len = read(fd, buf, buffer_size);
	buf[len] = '\0';
	return (len);
}
