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

typedef int(*t_builtinfunc_f)(t_context *context, t_shell *shell);

//@func
/*
** < builtin.c > */

int			builtin_run(t_AST_COMMAND *cmd, t_shell *shell);
/*
** < cd.c > */

int			builtin_cd(t_context *context, t_shell *shell);
/*
** < checks.c > */

t_res		check_no_opt(char *argv[], char *category);
t_res		check_arg_no_more_than( char *argv[], char *category, int max);
t_res		check_no_opt_arg(char *argv[], char *category);
/*
** < echo.c > */

int			builtin_echo(t_context *context, t_shell *shell);
/*
** < env.c > */

int			builtin_env(t_context *context, t_shell *shell);
/*
** < export.c > */

int			builtin_export(t_context *context, t_shell *shell);
/*
** < pwd.c > */

int			builtin_pwd(t_context *context, t_shell *shell);
/*
** < unset.c > */

void		builtin_unset();
/*
** < util.c > */

t_builtin	which_builtin(const char *str);
bool		is_builtin(const char *str);
bool		is_opt(char *str);
#endif