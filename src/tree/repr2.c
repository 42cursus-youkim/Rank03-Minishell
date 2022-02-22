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

void	ast_pipeline_repr(t_AST_SCRIPTS *pipeline, int level)
{
	int			i;
	const int	indent = level * INDENT_SIZE;

	printf(BBLU "%*s🔗PIPELINE\n" END, indent, "");
	if (pipeline->commands)
	{
		printf(BBLU "%*s[commands]\n" END, indent + INDENT_SIZE, "");
		i = -1;
		while (pipeline->commands[++i])
			ast_command_repr(pipeline->commands[i], level + 2);
	}
}

void	ast_script_repr(t_AST_SCRIPTS *pipeline)
{
	if (is_ast_command(pipeline))
		ast_command_repr(pipeline->commands[0], 0);
	else if (is_ast_pipeline(pipeline))
		ast_pipeline_repr(pipeline, 0);
}
