/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**new_arr(char **arr)
{
	int			i;
	char		**new;

	new = ft_calloc(sizeof(char *), 0);
	if (arr)
	{
		i = -1;
		while (arr[++i])
			ft_arr_append(&new, arr[i]);
	}
	return (new);
}

//	free all elements of arr then itself
void	del_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	ft_arr_len(char **arr)
{
	int		i;

	if (!arr)
		return (ERR);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
