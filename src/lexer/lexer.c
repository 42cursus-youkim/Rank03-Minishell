#include "minishell.h"

static bool	is_pipeline_token_valid(t_AST_type type[])
{
	if (type[1] == PIPELINE && (type[0] != WORD || type[2] == PIPELINE))
	{
		error_msg_return(
			(char *[]){BRED, MINISHELL, SYNTAX_ERROR, " `|'\n", END, NULL});
		return (false);
	}
	if (type[1] == PIPELINE && type[2] == TYPE_END)
	{
		error_msg_return(
			(char *[]){
			BRED, MINISHELL, SYNTAX_ERROR, " `|'\n",
			MULTILINE_ERROR, END, NULL});
		return (false);
	}
	return (true);
}

static bool	is_redirect_token_valid(t_AST_type type[], char *str)
{
	if (type[1] == REDIRECT && type[0] == REDIRECT)
	{
		error_msg_return(
			(char *[]){
			BRED, MINISHELL, SYNTAX_ERROR, " `", str, "'\n", END, NULL});
		return (false);
	}
	if ((type[0] == REDIRECT && type[1] == TYPE_END)
		|| (type[1] == REDIRECT && type[2] == TYPE_END))
	{
		error_msg_return(
			(char *[]){
			BRED, MINISHELL, SYNTAX_ERROR, " `newline'\n", END, NULL});
		return (false);
	}
	return (true);
}

static void	type_arr_init(t_AST_type type[3], t_token tokens[], int i)
{
	if (!i)
		type[0] = TYPE_START;
	else
		type[0] = tokens[i - 1].type;
	type[1] = tokens[i].type;
	if (tokens[i + 1].text)
		type[2] = tokens[i + 1].type;
	else
		type[2] = TYPE_END;
}

static bool	is_tokens_valid(t_token tokens[])
{
	int			i;
	t_AST_type	type[3];

	i = -1;
	while (tokens[++i].text)
	{
		type_arr_init(type, tokens, i);
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
		if (!tokens)
			return (NULL);
		if (!is_tokens_valid(tokens))
		{
			del_tokens(tokens);
			return (NULL);
		}
	}
	free(line);
	return (tokens);
}
