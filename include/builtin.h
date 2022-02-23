#ifndef BUILTIN_H
# define BUILTIN_H

//@func
/*
** < env1.c > */

t_dict	*new_env(char *envp[]);
void	del_env(t_dict *env);
char	**new_env_to_envp(t_dict *env);
/*
** < env2.c > */

void	env_set_exitcode(t_dict *env, int exitcode);
void	env_set(t_dict *env, char *str);
char	*env_get(t_dict *env, char *key);
void	env_print(t_dict *env);
/*
** < util.c > */

bool	is_builtin(char *str);
#endif