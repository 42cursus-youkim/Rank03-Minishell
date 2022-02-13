#include "minishell.h"

t_AST_type	tokentype_check(const char *str)
{
	if (is_str_equal(str, "|"))
		return (PIPELINE);
	if (is_str_equal(str, ";"))
		return (COMMAND);
	if (is_str_equal(str, "<") || is_str_equal(str, "<<")
		|| is_str_equal(str, ">") || is_str_equal(str, ">>"))
		return (REDIRECT);
	return (WORD);
}

int	quotes_index(const char *str)
{
	const int	single_i = ft_strchr_i(str, '\'');
	const int	double_i = ft_strchr_i(str, '\"');

	if (single_i != ERR && double_i != ERR)
	{
		if (single_i < double_i)
			return (single_i);
		else
			return (double_i);
	}
	if (single_i != ERR)
		return (single_i);
	if (double_i != ERR)
		return (double_i);
	return (ERR);
}

bool	is_expand_parameter(const char *str)
{
	const int	expand_i = ft_strchr_i(str, '$');
	const int	single_i = ft_strchr_i(str, '\'');
	const int	start_i = ft_strchr_i(str, '\"');
	int			end_i;

	if (start_i == ERR || expand_i == ERR
		|| (single_i != ERR && start_i > single_i))
		return (false);
	end_i = ft_strchr_i(&str[start_i + 1], '\"') + start_i + 1;
	if (expand_i > start_i && expand_i < end_i)
		return (true);
	return (false);
}

void	tokens_print(t_token tokens[])
{
	int			i;
	const char	*type_str[] = {
		BWHT "💬 WORD", BBLU "🔗 PIPELINE",
		BYEL "🔁 REDIRECT", BRED "🔥 COMMAND"};

	i = -1;
	while (tokens[++i].text)
		printf("[%2d] %-12s" BGRN "\t%s\n" END,
			i, type_str[tokens[i].type], tokens[i].text);
}

void	del_tokens(t_token tokens[])
{
	int	i;

	i = -1;
	while (tokens[++i].text)
		free(tokens[i].text);
	free(tokens);
}
