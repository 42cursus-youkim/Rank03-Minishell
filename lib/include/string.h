#ifndef STRING_H
# define STRING_H

//@func
/*
** < array.c > */

t_res	ft_arr_extend(char ***parr, char **src);
int		ft_arr_len(char **arr);
void	ft_arr_free(char **arr);
/*
** < join.c > */

char	*ft_arr_join(char **arr, char delimiter);
/*
** < new.c > */

char	*ft_strdup(const char *src);
int		ft_strappend(char **pstr, char *src);
/*
** < split.c > */

char	**ft_split(char const *str, char delimitor);
/*
** < util.c > */

int		ft_strlen(const char *str);
bool	is_str_equel(const char *str1, const char *str2);
#endif