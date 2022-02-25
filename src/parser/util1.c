#include "minishell.h"

t_redirect_op	redirection_option(char *str)
{
	if (is_str_equal(str, "<"))
		return (REDIR_INPUT);
	if (is_str_equal(str, "<<"))
		return (REDIR_HEREDOC);
	if (is_str_equal(str, ">"))
		return (REDIR_OUTPUT);
	if (is_str_equal(str, ">>"))
		return (REDIR_OUTPUT_APPEND);
	return (NOT_REDIR);
}

int	tokens_n_pipeline_count(int *size, t_token tokens[])
{
	int	i;
	int	count;
	int	len;

	count = 0;
	len = 0;
	i = -1;
	while (tokens[++i].text)
	{
		if (tokens[i].type == PIPELINE)
			count++;
		len++;
	}
	*size = len;
	return (count);
}

void	command_data_init(
	t_command_data *data, t_token tokens[], int begin, int end)
{
	int	i;

	data->name_index = -1;
	data->num_prefix = 0;
	data->num_suffix = 0;
	i = begin - 1;
	while (++i < end)
	{
		if (tokens[i].type == REDIRECT)
		{
			if (data->name_index == -1)
				data->num_prefix++;
			else
				data->num_suffix++;
			i++;
			continue ;
		}
		if (tokens[i].type == WORD)
		{
			if (data->name_index == -1)
				data->name_index = i;
			else
				data->num_suffix++;
		}
	}
}

int	ast_nodes_len(t_AST_NODE *nodes[])
{
	int	i;

	if (!nodes)
		return (ERR);
	i = 0;
	while (nodes[i])
		i++;
	return (i);
}
