#include "minishell.h"

static t_res	word_expansion(char **parr[], t_AST_NODE *node, t_dict *env)
{
	int		i;
	char	*temp_str;

	i = -1;
	while ((*parr)[++i])
	{
		if (i % 2)
			ft_str_replace(&(*parr)[i],
				new_str(env_get(env, node->expansions[i >> 1]->parameter)));
	}
	temp_str = new_str_join(*parr, '\0');
	ft_str_replace(&node->text, new_quotes_remove(temp_str));
	del_ast_expansions(node->expansions);
	node->expansions = NULL;
	del_arr(*parr);
	free(temp_str);
	return (OK);
}

static t_res	expansions_to_array(char **parr[], t_AST_NODE *node)
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

static t_res	node_expansion(t_AST_NODE *node, t_dict *env)
{
	char	**text_split;

	if (node->op == REDIR_HEREDOC)
	{
		del_ast_expansions(node->expansions);
		node->expansions = NULL;
	}
	if (!node->expansions || !node->expansions[0])
		return (UNSET);
	text_split = new_arr((char *[]){NULL});
	expansions_to_array(&text_split, node);
	word_expansion(&text_split, node, env);
	return (OK);
}

static t_res	commands_expansion(t_AST_COMMAND *command, t_dict *env)
{
	int	i;

	node_expansion(command->name, env);
	i = -1;
	if (command->prefixes)
	{
		while (command->prefixes[++i])
			node_expansion(command->prefixes[i], env);
	}
	i = -1;
	if (command->suffixes)
	{
		while (command->suffixes[++i])
			node_expansion(command->suffixes[i], env);
	}
	return (OK);
}

t_res	expander(t_AST_PIPELINE *pipeline, t_dict *env)
{
	int		i;

	i = -1;
	while (pipeline->commands[++i])
		commands_expansion(pipeline->commands[i], env);
	return (OK);
}
