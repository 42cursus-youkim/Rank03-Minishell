#ifndef TYPE_H
# define TYPE_H

# include <stdint.h>

typedef enum e_res
{
	OK = 0,
	ERR = -1,
	UNSET = -2,
}	t_res;

typedef void	(*t_del_f)(void *data);

#endif