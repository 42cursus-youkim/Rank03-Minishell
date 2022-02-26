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

typedef void(*t_builtinfunc_f)(t_context *context, t_shell *shell);

//@func
/*
** < builtin.c > */

int			builtin_run(t_AST_COMMAND *cmd, t_shell *shell);
/*
** < cd.c > */

void		builtin_cd(t_context *context, t_shell *shell);
/*
** < checks.c > */

t_res		check_no_opt(char *argv[], char *category);
t_res		check_arg_no_more_than( char *argv[], char *category, int max);
t_res		check_no_opt_arg(char *argv[], char *category);
/*
** < echo.c > */

void		builtin_echo(t_context *context, t_shell *shell);
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
void		builtin_env(t_context *context, t_shell *shell);
/*
** < export.c > */

void		builtin_export(t_dict *env);
/*
** < pwd.c > */

void		builtin_pwd(t_context *context, t_shell *shell);
/*
** < unset.c > */

void		builtin_unset();
/*
** < util.c > */

t_builtin	which_builtin(const char *str);
bool		is_builtin(const char *str);
bool		is_opt(char *str);
#endif