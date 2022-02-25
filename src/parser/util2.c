#include "minishell.h"

bool	is_ast_pipeline(t_AST_SCRIPT *script)
{
	return (script->commands_len > 1);
}

bool	is_ast_command(t_AST_SCRIPT *script)
{
	return (script->commands_len == 1);
}

t_res	prefixes_parsing(
	t_AST_COMMAND *command, t_token tokens[], int *prefix_i, int *i)
{
	const t_redirect_op	op = redirection_option(tokens[*i].text);

	command->prefixes[*prefix_i] = new_ast_redirect(
			tokens[*i + 1].text, tokens[*i + 1].expansions, op);
	*i += 1;
	if (!command->prefixes[(*prefix_i)++])
	{
		del_ast_command(command);
		return (ERR);
	}
	return (OK);
}

t_res	suffixes_parsing(
	t_AST_COMMAND *command, t_token tokens[], int *suffix_i, int *i)
{
	const t_redirect_op	op = redirection_option(tokens[*i].text);

	if (op == NOT_REDIR)
		command->suffixes[*suffix_i] = new_ast_word(
				tokens[*i].text, tokens[*i].expansions);
	else
		command->suffixes[*suffix_i] = new_ast_redirect(
				tokens[*i + 1].text, tokens[*i + 1].expansions, op);
	*i += (op != NOT_REDIR);
	if (!command->suffixes[(*suffix_i)++])
	{
		del_ast_command(command);
		return (ERR);
	}
	return (OK);
}
