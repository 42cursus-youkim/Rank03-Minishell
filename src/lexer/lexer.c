#include "minishell.h"

t_token	*tokenizer(char *arr[])
{
	t_token	*token;
	int		len;
	int		i;

	len = ft_arr_len(arr);
	token = (t_token *)malloc((len + 1) * sizeof(t_token));
	if (!token)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (is_metachar(&token[i], arr[i]))
			continue ;
		token[i].type = WORD;
		if (is_quotes(arr[i]) && !is_expand_parameter(arr[i]))
			token[i].text = new_str_slice(arr[i], 1, ft_strlen(arr[i]) - 1);
		else
			token[i].text = new_str(arr[i]);
	}
	token[i].text = NULL;
	return (token);
}
