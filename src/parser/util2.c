#include "minishell.h"

bool	is_ast_pipeline(t_AST_SCRIPT *script)
{
	return (script->commands_len > 1);
}

bool	is_ast_command(t_AST_SCRIPT *script)
{
	return (script->commands_len == 1);
}

int	ast_nodes_len(t_AST_NODE *nodes[])
{
	int	i;

	i = 0;
	while (nodes[i])
		i++;
	return (i);
}
