#include "minishell.h"

static t_res	buf_append_n_null_check(char **parr[], char **buf)
{
	if (!*buf)
		return (error_malloc_msg());
	if (ft_arr_append_free(parr, *buf) == ERR)
		return (free_n_return(buf, error_malloc_msg()));
	return (OK);
}

t_res	expansions_to_array(char **parr[], t_AST_NODE *node)
{
	const int	len = ft_strlen(node->text);
	int			i;
	int			begin;
	char		*buf;

	i = -1;
	begin = 0;
	while (node->expansions[++i])
	{
		buf = new_str_slice(node->text, begin, node->expansions[i]->begin);
		if (buf_append_n_null_check(parr, &buf) == ERR)
			return (ERR);
		buf = new_str_slice(node->text,
				node->expansions[i]->begin, node->expansions[i]->end + 1);
		if (buf_append_n_null_check(parr, &buf) == ERR)
			return (ERR);
		begin = node->expansions[i]->end + 1;
	}
	buf = new_str_slice(node->text, begin, len);
	if (buf_append_n_null_check(parr, &buf) == ERR)
		return (ERR);
	return (OK);
}
