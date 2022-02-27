#ifndef SYSTEM_H
# define SYSTEM_H

# define BUFFER_SIZE 42

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
//@func
/*
** < alloc.c > */

void	*ft_memset(void *b, char c, int space);
void	*ft_bzero(void *ptr, int n);
void	*ft_calloc(size_t size, size_t count);
/*
** < gnl.c > */

char	*ft_gnl(int fd);
/*
** < read.c > */

int		ft_read(int fd, char *buf, int buffer_size);
/*
** < write.c > */

int		ft_write(int fd, const char *str);
int		ft_writes(int fd, char *arr[]);
#endif