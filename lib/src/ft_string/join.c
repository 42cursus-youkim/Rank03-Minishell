/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*new_str_join(char **arr, char delimiter)
{
	int			i;
	char		*new;
	const int	arr_len = ft_arr_len(arr);

	if (!arr || !arr_len)
		return (NULL);
	new = new_str("");
	if (!new)
		return (NULL);
	i = -1;
	while (++i < arr_len - 1)
	{
		ft_str_extend(&new, arr[i]);
		ft_str_append(&new, delimiter);
	}
	ft_str_extend(&new, arr[i]);
	return (new);
}

char	*new_str_join_freed(char *delimiter_str, int size, t_tempstr map[])
{
	int		i;
	char	*new;

	if (!map || !delimiter_str || size < 0)
		return (NULL);
	new = new_str("");
	if (!new)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		ft_str_extend(&new, map[i].str);
		if (i < size - 1)
			ft_str_extend(&new, delimiter_str);
		if (map[i].will_free)
			free(map[i].str);
	}
	return (new);
}
