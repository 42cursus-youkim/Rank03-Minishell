#include "minishell.h"

static t_res	word_expansion(char **parr[], t_AST_NODE *node, t_dict *env)
{
	int		i;
	char	*temp_str;

	i = -1;
	while ((*parr)[++i])
	{
		if (i % 2)
			if (ft_str_replace(&(*parr)[i], new_str(
					env_get(env, node->expansions[i >> 1]->parameter))) == ERR)
				return (error_malloc_msg());
	}
	temp_str = new_str_join(*parr, '\0');
	if (!temp_str)
		return (error_malloc_msg());
	if (ft_str_replace(&node->text, new_quotes_remove(temp_str)) == ERR)
		return (ERR);
	del_ast_expansions(node->expansions);
	node->expansions = NULL;
	del_arr(*parr);
	free(temp_str);
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
	if (!text_split)
		return (error_malloc_msg());
	if (expansions_to_array(&text_split, node) == ERR)
	{
		del_arr(text_split);
		return (ERR);
	}
	if (word_expansion(&text_split, node, env) == ERR)
	{
		del_arr(text_split);
		return (ERR);
	}
	return (OK);
}

t_res	commands_expansion(t_AST_COMMAND *command, t_dict *env)
{
	int	i;

	if (node_expansion(command->name, env) == ERR)
		return (ERR);
	i = -1;
	if (command->prefixes)
	{
		while (command->prefixes[++i])
			if (node_expansion(command->prefixes[i], env) == ERR)
				return (ERR);
	}
	i = -1;
	if (command->suffixes)
	{
		while (command->suffixes[++i])
			if (node_expansion(command->suffixes[i], env) == ERR)
				return (ERR);
	}
	return (OK);
}

t_res	expander(t_AST_SCRIPT *script, t_dict *env)
{
	int		i;

	i = -1;
	while (script->commands[++i])
	{
		if (commands_expansion(script->commands[i], env) == ERR)
		{
			del_ast_script(script);
			return (ERR);
		}
	}
	return (OK);
}
