#ifndef FT_MATH_H
# define FT_MATH_H

//@func
/*
** < check.c > */

bool	is_alpha(char c);
bool	is_digit(char c);
bool	is_overflow(int n, int sign);
bool	is_whitespace(char c);
/*
** < compare.c > */

int		ft_digit_len(int n);
int		ft_max(int a, int b);
/*
** < math.c > */

char	*new_itoa(int n);
char	*ft_bool_to_str(bool b);
t_res	ft_atoi(const char *str, int *n);
#endif