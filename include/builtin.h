#ifndef BUILTIN_H
# define BUILTIN_H

//@func
/*
** < env.c > */

void	env_set(t_dict *env, char *str);
char	*env_get(t_dict *env, char *key);
t_dict	*new_env(char *envp[]);
void	env_print(t_dict *env);
char	**new_env_to_envp(t_dict *env);
/*
** < util.c > */

bool	is_builtin(char *str);
#endif