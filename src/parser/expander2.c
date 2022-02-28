#include "minishell.h"

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
		ft_arr_append_free(parr, buf);
		buf = new_str_slice(node->text,
				node->expansions[i]->begin, node->expansions[i]->end + 1);
		ft_arr_append_free(parr, buf);
		begin = node->expansions[i]->end + 1;
	}
	buf = new_str_slice(node->text, begin, len);
	ft_arr_append_free(parr, buf);
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
