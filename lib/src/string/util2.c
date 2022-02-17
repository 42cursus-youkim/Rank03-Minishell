#include "libft.h"

//	replace str_p with new. new will not be allocated, it's just movced
t_res	ft_str_replace(char **str_p, char *new)
{
	if (!str_p || !new)
		return (ERR);
	free(*str_p);
	*str_p = new;
	return (OK);
}
