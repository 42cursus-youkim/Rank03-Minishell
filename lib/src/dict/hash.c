#include "libft.h"

//	FNV-1a hash algorithm
uint64_t	yhash_fnv1a(const char *key)
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