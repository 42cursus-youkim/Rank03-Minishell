/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	command_i = -1;
	while (tokens[++i].text)
	{
		if (tokens[i].type == PIPELINE)
		{
			commands[++command_i] = command_parsing(tokens, begin, i);
			begin = i + 1;
		}
	}
	commands[++command_i] = command_parsing(tokens, begin, i);
	return (OK);
}

//	parser
t_AST_SCRIPT	*new_script_from_tokens(t_token tokens[])
{
	t_AST_SCRIPT	*script;
	t_AST_COMMAND	**commands;
	int				tokens_size;
	const int		pipe_count = tokens_n_pipeline_count(&tokens_size, tokens);
	int				commands_len;

	commands_len = pipe_count + 1;
	commands = ft_calloc(sizeof(t_AST_COMMAND *), commands_len);
	if (!pipe_count)
		(commands)[0] = command_parsing(tokens, 0, tokens_size);
	else
		command_parsing_with_pipe(commands, tokens);
	script = new_ast_script(commands, commands_len);
	del_tokens(tokens);
	return (script);
}
