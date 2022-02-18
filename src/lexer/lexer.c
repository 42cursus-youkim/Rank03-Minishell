#include "minishell.h"

static char	*new_quotes_remove(char *str, int quote_i)
{
	char	**split_words;
	char	*new;

	split_words = new_str_split(str, str[quote_i]);
	new = new_str_join(split_words, '\0');
	del_arr(split_words);
	return (new);
}

static char	*new_expand_parameter(char *str)
{
	char	*new;

	new = new_str("\"");
	ft_str_extend(&new, str);
	ft_str_extend(&new, "\"");
	return (new);
}

t_token	*tokenizer(char *arr[])
{
	t_token	*tokens;
	int		len;
	int		i;
	int		quote_i;

	len = ft_arr_len(arr);
	tokens = (t_token *)malloc((len + 1) * sizeof(t_token));
	if (!tokens)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		tokens[i].type = tokentype_check(arr[i]);
		quote_i = quotes_index(arr[i]);
		if (quote_i != ERR && !is_expand_parameter(arr[i]))
			tokens[i].text = new_quotes_remove(arr[i], quote_i);
		else if (quote_i == ERR && ft_strchr_i(arr[i], '$') != ERR)
			tokens[i].text = new_expand_parameter(arr[i]);
		else
			tokens[i].text = new_str(arr[i]);
	}
	tokens[i].text = NULL;
	del_arr(arr);
	return (tokens);
}
