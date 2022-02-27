#include "minishell.h"

t_AST_type	tokentype_check(t_scan_node *node)
{
	const char	*str = node->text;

	if (is_str_equal(str, "|"))
		return (PIPELINE);
	if (is_str_equal(str, "<") || is_str_equal(str, "<<")
		|| is_str_equal(str, ">") || is_str_equal(str, ">>"))
		return (REDIRECT);
	return (WORD);
}

void	tokens_print(t_token tokens[])
{
	int			i;
	const char	*type_str[] = {
		BWHT "💬 WORD", BBLU "🔗 PIPELINE",
		BYEL "🔁 REDIRECT", BRED "🔥 COMMAND"};

	i = -1;
	while (tokens[++i].text)
	{
		printf("[%2d] %-12s" BGRN "\t%s\n" END,
			i, type_str[tokens[i].type], tokens[i].text);
		if (tokens[i].expansions)
			expansions_print(tokens[i].expansions);
	}
}

void	del_tokens(t_token tokens[])
{
	int	i;

	i = -1;
	while (tokens[++i].text)
	{
		free(tokens[i].text);
		del_ast_expansions(tokens[i].expansions);
	}
	free(tokens);
}

bool	is_pipeline_token_valid(t_AST_type type[], t_dict *env)
{
	if (type[1] == PIPELINE && (type[0] != WORD || type[2] == PIPELINE))
	{
		error_with_exitcode(
			(char *[]){BRED, MINISHELL, SYNTAX_ERROR, " `|'\n", END, NULL},
			env, 2);
		return (false);
	}
	if (type[1] == PIPELINE && type[2] == TYPE_END)
	{
		error_with_exitcode(
			(char *[]){
			BRED, MINISHELL, SYNTAX_ERROR, " `|'\n",
			MULTILINE_ERROR, END, NULL}, env, 2);
		return (false);
	}
	return (true);
}

bool	is_redirect_token_valid(t_AST_type type[], char *str, t_dict *env)
{
	if (type[1] == REDIRECT && type[0] == REDIRECT)
	{
		error_with_exitcode(
			(char *[]){
			BRED, MINISHELL, SYNTAX_ERROR, " `", str, "'\n", END, NULL},
			env, 2);
		return (false);
	}
	if ((type[0] == REDIRECT && type[1] == TYPE_END)
		|| (type[1] == REDIRECT && type[2] == TYPE_END))
	{
		error_with_exitcode(
			(char *[]){
			BRED, MINISHELL, SYNTAX_ERROR, " `newline'\n", END, NULL}, env, 2);
		return (false);
	}
	return (true);
}
