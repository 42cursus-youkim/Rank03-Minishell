#include "minishell.h"

static void	ast_nodes_repr(t_AST_NODE *nodes[], int level)
{
	int		i;

	if (!nodes)
		return ;
	i = -1;
	while (nodes[++i])
		ast_node_repr(nodes[i], level);
}

void	ast_command_repr(t_AST_COMMAND *cmd, int level)
{
	const int	indent = level * INDENT_SIZE;

	printf(BRED "%*s🔥COMMAND\n" END, indent, "");
	printf(BRED "%*s[name]\n" END, indent + INDENT_SIZE, "");
	ast_node_repr(cmd->name, level + 2);
	if (cmd->prefixes)
	{
		printf(BRED "%*s[prefixes]\n" END, indent + INDENT_SIZE, "");
		ast_nodes_repr(cmd->prefixes, level + 2);
	}
	if (cmd->suffixes)
	{
		printf(BRED "%*s[suffixes]\n" END, indent + INDENT_SIZE, "");
		ast_nodes_repr(cmd->suffixes, level + 2);
	}
}
