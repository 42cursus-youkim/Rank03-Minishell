#include "minishell.h"

t_token	*tokenizer(char *arr[])
{
	t_token	*tokens;
	int		len;
	int		i;

	len = ft_arr_len(arr);
	tokens = (t_token *)malloc((len + 1) * sizeof(t_token));
	if (!tokens)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		tokens[i].type = tokentype_check(arr[i]);
		if (is_quotes(arr[i]) && !is_expand_parameter(arr[i]))
			tokens[i].text = new_str_slice(arr[i], 1, ft_strlen(arr[i]) - 1);
		else
			tokens[i].text = new_str(arr[i]);
	}
	tokens[i].text = NULL;
	return (tokens);
}
