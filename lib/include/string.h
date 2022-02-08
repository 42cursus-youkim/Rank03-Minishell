#ifndef STRING_H
# define STRING_H

//@func
/*
** < split.c > */

char	**ft_split(char const *s, char c);
/*
** < utils.c > */

int		ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_strappend(char **pstr, char *src);
#endif