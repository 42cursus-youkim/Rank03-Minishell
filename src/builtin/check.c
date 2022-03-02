/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_res	check_no_opt(char *argv[], char *category)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (is_opt(argv[i]))
			return (error_msg_bad_opt(category, argv[i]));
	return (OK);
}

t_res	check_no_opt_arg(char *argv[], char *category)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (is_opt(argv[i]))
			return (error_msg_bad_opt(category, argv[i]));
		else
			return (error_msg_category(category, "too many arguments"));
	}
	return (OK);
}
