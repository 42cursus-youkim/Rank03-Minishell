#ifndef SYSTEM_H
# define SYSTEM_H

# define BUFFER_SIZE 42

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
//@func
/*
** < calloc.c > */

void	*ft_calloc(size_t size, size_t count);
#endif