#include "minishell.h"

static t_AST_NODE	**new_prefixes_n_suffixes(int size)
{
	t_AST_NODE	**new;

	if (size)
		new = ft_calloc(sizeof(t_AST_NODE *), size);
	if (!size || !new)
		return (NULL);
	return (new);
}

t_AST_COMMAND	*new_ast_command(t_token tokens[], t_command_data data)
{
	t_AST_COMMAND	*new;

	new = ft_calloc(sizeof(t_AST_COMMAND), 0);
	if (data.name_index == -1)
		new->name = new_ast_word("", NULL);
	else
		new->name = new_ast_word(tokens[data.name_index].text,
				tokens[data.name_index].expansions);
	new->prefixes = new_prefixes_n_suffixes(data.num_prefix);
	new->suffixes = new_prefixes_n_suffixes(data.num_suffix);
	api_copy_pipe((t_fd[IO_SIZE]){UNSET, UNSET}, new->io);
	new->is_faulty = false;
	return (new);
}

t_AST_SCRIPT	*new_ast_script(t_AST_COMMAND *commands[], int commands_len)
{
	t_AST_SCRIPT	*script;

	script = ft_calloc(sizeof(t_AST_SCRIPT), 0);
	script->commands = commands;
	script->commands_len = commands_len;
	return (script);
}
