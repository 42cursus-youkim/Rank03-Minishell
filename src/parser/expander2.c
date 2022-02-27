#include "minishell.h"

static t_res	buf_append_n_null_check(char **parr[], char **buf)
{
	if (!*buf)
		return (ERR);
	if (ft_arr_append_free(parr, *buf) == ERR)
		return (free_n_return(buf, ERR));
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

bool	is_substitution_valid(char *str)
{
	const int	len = ft_strlen(str);
	int			i;

	if (str[len - 1] != '}')
		return (true);
	if (len == 3)
		return (false);
	i = 2;
	if (!is_1stchar_valid(str[i]) || str[i] == '{')
		return (false);
	while (++i < len - 1)
	{
		if (!is_variable_char_valid(str[i]))
			return (false);
	}
	return (true);
}
