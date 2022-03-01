#ifndef API_H
# define API_H

//@func
/*
** < env1.c > */

t_dict	*new_env(char *envp[]);
void	del_env(t_dict *env);
char	**new_env_to_envp(t_dict *env);
void	env_print(t_dict *env);
/*
** < env2.c > */

void	env_set_exitcode(t_dict *env, int exitcode);
t_res	env_set(t_dict *env, char *str);
char	*env_get(t_dict *env, char *key);
/*
** < path.c > */

char	*new_path_resolved(char *path, t_dict *env);
char	**new_names_from_path(char *name, t_dict *env);
/*
** < signal.c > */

int		api_handle_status(int status);
/*
** < tilde.c > */

bool	is_path_tilde_expansion(char *path);
t_res	path_replace_tilde(char **path_p, t_dict *env);
/*
** < util.c > */

void	api_exit(t_shell *shell, int exitcode);
void	api_show_logo(char *file);
#endif