/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H

# define BUFFER_SIZE 1024

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
//@func
/*
** < alloc.c > */

void	*ft_memset(void *b, char c, int space);
void	*ft_bzero(void *ptr, int n);
void	*ft_calloc(size_t size, size_t count);
void	ft_try_free(void *ptr);
void	ft_free(void *ptr);
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