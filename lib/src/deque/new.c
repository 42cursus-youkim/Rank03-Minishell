#include "libft.h"

t_dnode	*new_dnode(char *str)
{
	t_dnode	*node;

	node = malloc(sizeof(t_dnode));
	if (!node)
		return (NULL);
	node->str = str;
	node->lower = NULL;
	node->upper = NULL;
	return (node);
}

/*	create new double-linked list with head and tail.
	locating beginning and end of list is done by size,
	since they're endless loop.
	first argument goes to head(top), last to tail(bottom)!
*/
t_deque	*new_deque(int size, char *str[])
{
	t_deque	*deque;

	deque = malloc(sizeof(t_deque));
	if (!deque)
		return (NULL);
	deque->head = NULL;
	deque->tail = NULL;
	deque->size = 0;
	if (!str | !size)
		return (NULL);
	// while (--size >= 0)
	// 	deque_push(deque, new_dnode(str[size]));
	return (deque);
}

void	del_deque(t_deque *deque)
{
	t_dnode	*curs;
	t_dnode	*temp;

	if (!deque)
		return ;
	curs = deque->head;
	while (--deque->size >= 0)
	{
		temp = curs;
		curs = curs->lower;
		free(temp);
	}
	free(deque);
}
