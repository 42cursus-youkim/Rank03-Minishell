/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_argv_from_cmd(char *executable, t_AST_COMMAND *cmd)
{
	int			i;
	char		**argv;
	int			argv_idx;
	const int	len = ast_nodes_len(cmd->suffixes);

	if (len == ERR)
		return (new_arr((char *[]){executable, NULL}));
	argv = ft_calloc(sizeof(char *), len + 1);
	argv_idx = 0;
	argv[argv_idx] = new_str(executable);
	i = -1;
	while (++i < len)
		if (cmd->suffixes[i]->type == WORD)
			argv[++argv_idx] = new_str(cmd->suffixes[i]->text);
	return (argv);
}
