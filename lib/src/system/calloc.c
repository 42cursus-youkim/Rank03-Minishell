#include "libft.h"

void	*ft_calloc(size_t size, size_t count)
{
	size_t			i;
	char			*ptr;
	const size_t	allocated_space = count * (size + 1);

	ptr = malloc(allocated_space);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < allocated_space)
		ptr[i++] = 0;
	return ((void *)ptr);
}
