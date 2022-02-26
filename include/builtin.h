#ifndef BUILTIN_H
# define BUILTIN_H

typedef enum e_builtin
{
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin;

//@func
/*
** < builtin.c > */

void		builtins_exec(t_AST_COMMAND *cmd, t_shell *shell);
/*
** < echo.c > */

bool		is_opt_nonewline_valid(char *str, bool *is_newline_p);
void		echo_inner(int i, int len, char *str);
void		builtin_echo(t_context *context);
/*
** < env1.c > */

t_dict		*new_env(char *envp[]);
void		del_env(t_dict *env);
char		**new_env_to_envp(t_dict *env);
/*
** < env2.c > */

void		env_set_exitcode(t_dict *env, int exitcode);
void		env_set(t_dict *env, char *str);
char		*env_get(t_dict *env, char *key);
void		env_print(t_dict *env);
/*
** < pwd.c > */

void		builtin_pwd(t_dict *env);
/*
** < util.c > */

t_builtin	which_builtin(char *str);
bool		is_builtin(char *str);
#endif