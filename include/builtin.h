#ifndef BUILTIN_H
# define BUILTIN_H

//@func
/*
** < env.c > */

void	env_set(t_dict *env, char *str);
t_dict	*new_env(char *envp[]);
void	env_print(t_dict *env);
#endif