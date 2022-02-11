#include "minishell.h"

bool	is_metachar(t_token *token, const char *str)
{
	if (is_str_equal(str, "|"))
		token->type = PIPELINE;
	else if (is_str_equal(str, ";"))
		token->type = COMMAND;
	else if (is_str_equal(str, "<") || is_str_equal(str, "<<")
		|| is_str_equal(str, ">") || is_str_equal(str, ">>"))
		token->type = REDIRECT;
	else
		return (false);
	token->text = new_str(str);
	return (true);
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

void	token_print(t_token token[])
{
	int	i;

	i = 0;
	while (token[i].text)
	{
		printf("[%d] text: %s\ttype: %d\n", i, token[i].text, token[i].type);
		i++;
	}
}

void	del_token(t_token token[])
{
	int	i;

	i = -1;
	while (token[++i].text)
		free(token[i].text);
	free(token);
}
