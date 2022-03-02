/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_syscall("getcwd");
	return (cwd);
}

int	builtin_pwd(t_context *context, t_shell *shell)
{
	char	*cwd;

	(void)context;
	(void)shell;
	cwd = new_cwd();
	if (!cwd)
		return (EXIT_FAILURE);
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
