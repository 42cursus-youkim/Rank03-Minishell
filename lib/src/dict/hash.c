/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	FNV-1a hash algorithm
uint64_t	hash_fnv1a(const char *key)
{
	int			i;
	uint64_t	hash;

	i = -1;
	hash = FNV_OFFSET;
	while (key[++i])
	{
		hash ^= key[i];
		hash *= FNV_PRIME;
	}
	return (hash);
}
