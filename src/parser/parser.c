#include "minishell.h"

static t_AST_COMMAND	*command_parsing(t_token tokens[], int begin, int end)
{
	t_command_data	data;
	t_AST_COMMAND	*command;
	int				i;
	int				prefix_i;
	int				suffix_i;

	command_data_init(&data, tokens, begin, end);
	command = new_ast_command(tokens, data);
	if (!command)
		return (NULL);
	i = begin - 1;
	prefix_i = 0;
	suffix_i = 0;
	while (++i < end)
	{
		if (data.name_index == -1 || i < data.name_index)
			if (prefixes_parsing(command, tokens, &prefix_i, &i) == ERR)
				return (NULL);
		if (i == data.name_index)
			continue ;
		if (data.name_index != -1 && i > data.name_index)
			if (suffixes_parsing(command, tokens, &suffix_i, &i) == ERR)
				return (NULL);
	}
	return (command);
}

static t_res	command_parsing_error(
	t_AST_COMMAND *commands[], t_token tokens[])
{
	del_ast_commands(commands);
	del_tokens(tokens);
	return (ERR);
}

static t_res	command_parsing_with_pipe(
	t_AST_COMMAND *commands[], t_token tokens[])
{
	int	i;
	int	begin;
	int	command_i;

	i = -1;
	begin = 0;
	command_i = -1;
	while (tokens[++i].text)
	{
		if (tokens[i].type == PIPELINE)
		{
			commands[++command_i] = command_parsing(tokens, begin, i);
			if (!commands[command_i])
				return (command_parsing_error(commands, tokens));
			begin = i + 1;
		}
	}
	commands[++command_i] = command_parsing(tokens, begin, i);
	if (!commands[command_i])
		return (command_parsing_error(commands, tokens));
	return (OK);
}

t_res	commands_for_parser(
	t_AST_COMMAND **commands[], t_token tokens[], int *commands_len)
{
	int				tokens_size;
	const int		pipe_count = tokens_n_pipeline_count(&tokens_size, tokens);

	*commands_len = pipe_count + 1;
	*commands = ft_calloc(sizeof(t_AST_COMMAND *), *commands_len);
	if (!*commands)
	{
		del_tokens(tokens);
		return (ERR);
	}
	if (!pipe_count)
	{
		(*commands)[0] = command_parsing(tokens, 0, tokens_size);
		if (!(*commands)[0])
			return (command_parsing_error(*commands, tokens));
	}
	else
		if (command_parsing_with_pipe(*commands, tokens) == ERR)
			return (ERR);
	return (OK);
}

t_AST_SCRIPT	*parser(t_token tokens[])
{
	t_AST_SCRIPT	*script;
	t_AST_COMMAND	**commands;
	int				commands_len;

	if (commands_for_parser(&commands, tokens, &commands_len) == ERR)
		return (NULL);
	script = new_ast_script(commands, commands_len);
	if (script == NULL)
	{
		command_parsing_error(commands, tokens);
		return (NULL);
	}
	del_tokens(tokens);
	return (script);
}
