#include "libft.h"

//	returns ptr
void	*ft_memset(void *b, char c, int space)
{
	int		i;
	char	*ptr;

	ptr = (char *)b;
	i = 0;
	while (i < space)
		ptr[i++] = c;
	return ((void *)ptr);
}

//	returns ptr set to 0
void	*ft_bzero(void *ptr, int n)
{
	return (ft_memset(ptr, '\0', n));
}

void	*ft_calloc(size_t size, size_t count)
{
	char			*ptr;
	const size_t	allocated_space = size * (count + 1);

	ptr = malloc(allocated_space);
	if (!ptr)
	{
		error_syscall("ft_calloc");
		exit(EXIT_FAILURE);
	}
	return (ft_bzero(ptr, allocated_space));
}

void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
