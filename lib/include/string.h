#ifndef STRING_H
# define STRING_H

//@func
/*
** < array.c > */

t_res	ft_arr_extend(char ***parr, char **src);
int		ft_arr_len(char **arr);
void	ft_arr_free(char **arr);
/*
** < split.c > */

char	**ft_split(char const *str, char delimitor);
/*
** < utils.c > */

int		ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_strappend(char **pstr, char *src);
#endif