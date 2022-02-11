#include "minishell.h"

t_tokentype	tokentype_check(const char *str)
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

bool	is_quotes(const char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
		return (true);
	return (false);
}

bool	is_expand_parameter(const char *str)
{
	if (str[0] == '\"' && (ft_strchr_i(str, '$') != ERR))
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
		printf("[%2d] " BGRN "%-12s" END "%s\n" END,
			i, tokens[i].text, type_str[tokens[i].type]);
}

void	del_tokens(t_token tokens[])
{
	int	i;

	i = -1;
	while (tokens[++i].text)
		free(tokens[i].text);
	free(tokens);
}
