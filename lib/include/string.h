#ifndef STRING_H
# define STRING_H

typedef struct s_tempstr
{
	char	*str;
	bool	will_free;
}	t_tempstr;

//@func
/*
** < array.c > */

t_res	ft_arr_append(char **parr[], char *str);
t_res	ft_arr_extend(char **parr[], char *src[]);
int		ft_arr_len(char **arr);
char	**new_arr(char **arr);
void	del_arr(char **arr);
/*
** < split.c > */

char	**new_str_split(char const *str, char delimitor);
/*
** < join.c > */

char	*new_str_join(char **arr, char delimiter);
char	*new_str_join_freed(char *delimiter_str, int size, t_tempstr map[]);
/*
** < new.c > */

char	*new_str(const char *src);
char	*new_str_slice(char *str, int begin, int end);
int		ft_str_append(char **pstr, char c);
int		ft_str_extend(char **pstr, char *src);
/*
** < util.c > */

int		ft_strlen(const char *str);
bool	is_str_equal(const char *str1, const char *str2);
int		ft_strchr_i(const char *str, char c);
int		ft_strrchr_i(const char *str, char c);
void	ft_arr_print(char **arr);
#endif