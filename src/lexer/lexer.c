#include "minishell.h"

static void	type_arr_init(t_AST_type type[3], t_token tokens[], int i)
{
	if (!i)
		type[0] = TYPE_START;
	else
		type[0] = tokens[i - 1].type;
	type[1] = tokens[i].type;
	if (tokens[i + 1].text)
		type[2] = tokens[i + 1].type;
	else
		type[2] = TYPE_END;
}

static bool	is_tokens_valid(t_token tokens[], t_dict *env)
{
	int			i;
	t_AST_type	type[3];

	i = -1;
	while (tokens[++i].text)
	{
		type_arr_init(type, tokens, i);
		if (!is_pipeline_token_valid(type, env)
			|| !is_redirect_token_valid(type, tokens[i].text, env))
			return (false);
	}
	return (true);
}

t_token	*new_tokens_from_line(char *line, t_dict *env)
{
	t_list	*scan_list;
	t_token	*tokens;

	scan_list = NULL;
	tokens = NULL;
	if (scanner(&scan_list, line, env) == ERR)
		del_list(&scan_list, del_scan_node);
	else
	{
		tokens = new_tokens_from_list(scan_list);
		if (!tokens)
		{
			env_set_exitcode(env, EXIT_FAILURE);
			return (NULL);
		}
		if (!is_tokens_valid(tokens, env))
		{
			del_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
