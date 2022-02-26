#include "libft.h"

//	replace str_p with new. new will not be allocated, it's just moved
t_res	ft_str_replace(char **str_p, char *new)
{
	if (!str_p || !new)
		return (ERR);
	free(*str_p);
	*str_p = new;
	return (OK);
}

static int	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}

/* append a character 'c' to the end of the string "pstr"
*/
int	ft_str_append(char **pstr, char c)
{
	const int	len = ft_strlen(*pstr);
	char		*new;

	if (c == '\0')
		return (OK);
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (ERR);
	ft_strcpy(new, *pstr);
	new[len] = c;
	free(*pstr);
	*pstr = new;
	return (OK);
}

/*	extends string "src" to "pstr"
	ex: "hello " + "world" = "hello world"
*/
int	ft_str_extend(char **pstr, char *src)
{
	const int	org_len = ft_strlen(*pstr);
	const int	src_len = ft_strlen(src);
	const int	new_len = org_len + src_len;
	char		*new;

	new = ft_calloc(sizeof(char), new_len);
	if (!new)
		return (ERR);
	ft_strcpy(new, *pstr);
	ft_strcpy(new + org_len, src);
	free(*pstr);
	*pstr = new;
	return (new_len);
}

int	ft_str_extend_freed(char **pstr, char *src)
{
	const int	result = ft_str_extend(pstr, src);

	free(src);
	return (result);
}
