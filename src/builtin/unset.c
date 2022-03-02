/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_context *context, t_shell *shell)
{
	int			i;
	t_res		res;
	const int	len = ft_arr_len(context->argv);

	if (check_no_opt(context->argv, "export") != OK)
		return (EXIT_FAILURE);
	res = OK;
	i = 0;
	while (++i < len)
		res = dict_drop(shell->env, context->argv[i]);
	if (res != OK)
		return (EXIT_FAILURE);
	return (OK);
}
