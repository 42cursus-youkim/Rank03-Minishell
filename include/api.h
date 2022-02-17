#ifndef API_H
# define API_H

//@func
/*
** < path.c > */

char	*new_path_resolved(char *path, t_dict *env);
char	**new_raw_path(t_dict *env);
char	**new_path(t_dict *env);
#endif