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
/*
** < write.c > */

int		ft_write(int fd, const char *str);
int		ft_writes(int fd, char *arr[]);
#endif