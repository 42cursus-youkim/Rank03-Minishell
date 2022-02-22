#include "minishell.h"

bool	is_ast_pipeline(t_AST_SCRIPTS *pipeline)
{
	return (pipeline->commands_len > 1);
}

bool	is_ast_command(t_AST_SCRIPTS *pipeline)
{
	return (pipeline->commands_len == 1);
}
