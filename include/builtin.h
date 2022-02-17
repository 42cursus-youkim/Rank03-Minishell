#ifndef BUILTIN_H
# define BUILTIN_H

//@func
/*
** < env.c > */

void	env_set(t_dict *env, char *str);
char	*env_get(t_dict *env, char *key);
t_dict	*new_env(char *envp[]);
void	env_print(t_dict *env);
char	**new_arr_env(t_dict *env);
#endif