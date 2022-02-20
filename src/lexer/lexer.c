#include "minishell.h"

static bool	is_pipeline_token_valid(t_AST_type type[])
{
	if (type[1] == PIPELINE && (type[0] != WORD || type[2] == PIPELINE))
	{
		printf(BRED "minishell: syntax error near unexpected token `|'\n" END);
		return (false);
	}
	if (type[1] == PIPELINE && type[2] == TYPE_END)
	{
		printf(BRED "minishell: syntax error near unexpected token `|'\n");
		printf("multiline is not supported :(\n" END);
		return (false);
	}
	return (true);
}

static bool	is_redirect_token_valid(t_AST_type type[], char *str)
{
	if (type[1] == REDIRECT && type[0] == REDIRECT)
	{
		printf(BRED "minishell: syntax error near unexpected token ");
		printf("`%s'\n" END, str);
		return (false);
	}
	if (type[1] == REDIRECT && type[2] == TYPE_END)
	{
		printf(BRED
			"minishell: syntax error near unexpected token `newline'\n" END);
		return (false);
	}
	return (true);
}

static bool	is_tokens_valid(t_token tokens[])
{
	int			i;
	t_AST_type	type[3];

	i = -1;
	if (tokens[++i].type == PIPELINE)
	{
		printf(BRED "minishell: syntax error near unexpected token `|'\n" END);
		return (false);
	}
	while (tokens[++i].text)
	{
		type[0] = tokens[i - 1].type;
		type[1] = tokens[i].type;
		if (tokens[i + 1].text)
			type[2] = tokens[i + 1].type;
		else
			type[2] = TYPE_END;
		if (!is_pipeline_token_valid(type)
			|| !is_redirect_token_valid(type, tokens[i].text))
			return (false);
	}
	return (true);
}

t_token	*lexer(char *line)
{
	t_list	*scan_list;
	t_token	*tokens;

	scan_list = NULL;
	tokens = NULL;
	if (scanner(&scan_list, line) == ERR)
		del_list(&scan_list, del_scan_node);
	else
	{
		tokens = tokenizer(scan_list);
		if (!is_tokens_valid(tokens))
		{
			del_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
