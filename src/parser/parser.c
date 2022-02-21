#include "minishell.h"

static t_res	prefixes_parsing(
	t_AST_COMMAND *command, t_token tokens[], int *prefix_i, int *i)
{
	const t_redirect_op	op = redirection_option(tokens[*i].text);

	command->prefixes[*prefix_i] = new_ast_redirect(
			tokens[*i + 1].text, tokens[*i + 1].expansions, op);
	*i += 1;
	if (!command->prefixes[(*prefix_i)++])
		return (ERR);
	return (OK);
}

static t_res	suffixes_parsing(
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
		return (ERR);
	return (OK);
}

static t_AST_COMMAND	*command_parsing(t_token tokens[], int begin, int end)
{
	t_command_data	data;
	t_AST_COMMAND	*command;
	int				i;
	int				prefix_i;
	int				suffix_i;

	command_data_init(&data, tokens, begin, end);
	command = new_command(tokens, data);
	i = begin - 1;
	prefix_i = 0;
	suffix_i = 0;
	while (++i < end)
	{
		if (data.name_index == -1 || i < data.name_index)
			prefixes_parsing(command, tokens, &prefix_i, &i);
		if (i == data.name_index)
			continue ;
		if (data.name_index != -1 && i > data.name_index)
			suffixes_parsing(command, tokens, &suffix_i, &i);
	}
	return (command);
}

static t_res	command_parsing_with_pipe(
	t_AST_COMMAND *commands[], t_token tokens[])
{
	int	i;
	int	begin;
	int	command_i;

	i = -1;
	begin = 0;
	command_i = 0;
	while (tokens[++i].text)
	{
		if (tokens[i].type == PIPELINE)
		{
			commands[command_i] = command_parsing(tokens, begin, i);
			command_i++;
			begin = i + 1;
		}
	}
	commands[command_i] = command_parsing(tokens, begin, i);
	return (OK);
}

t_AST_PIPELINE	*parser(t_token tokens[])
{
	int				tokens_size;
	const int		pipe_count = tokens_n_pipeline_count(&tokens_size, tokens);
	const int		commands_len = commands_size(pipe_count);
	t_AST_PIPELINE	*pipeline;
	t_AST_COMMAND	**commands;

	commands = ft_calloc(sizeof(t_AST_COMMAND *), commands_len);
	if (!commands)
	{
		del_tokens(tokens);
		return (NULL);
	}
	if (!pipe_count)
		commands[0] = command_parsing(tokens, 0, tokens_size);
	else
		command_parsing_with_pipe(commands, tokens);
	pipeline = new_ast_pipeline(commands, commands_len);
	del_tokens(tokens);
	return (pipeline);
}
