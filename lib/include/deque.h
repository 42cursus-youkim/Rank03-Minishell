#ifndef DEQUE_H
# define DEQUE_H

typedef struct s_dnode
{
	char			*str;
	struct s_dnode	*lower;
	struct s_dnode	*upper;
}	t_dnode;

typedef struct s_deque
{
	t_dnode			*head;
	t_dnode			*tail;
	int				size;
}	t_deque;

//@func
/*
** < new.c > */

t_dnode	*new_dnode(char *str);
t_deque	*new_deque(int size, char *str[]);
void	del_deque(t_deque *deque);
#endif