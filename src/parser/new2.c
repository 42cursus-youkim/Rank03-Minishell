#include "minishell.h"

t_AST_PIPELINE	*new_ast_pipeline(t_AST_COMMAND *commands[])
{
	t_AST_PIPELINE	*pipeline;

	pipeline = malloc(sizeof(t_AST_PIPELINE));
	if (!pipeline)
		return (NULL);
	pipeline->commands = commands;
	return (pipeline);
}
