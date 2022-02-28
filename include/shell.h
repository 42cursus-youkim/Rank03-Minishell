#ifndef SHELL_H
# define SHELL_H

# include "dict.h"
# include "ast_type.h"

typedef struct s_prompt
{
	char	*user;
	char	*ps1;
	char	*ps2;
	char	*line;
}	t_prompt;

typedef struct s_shell
{
	t_dict			*env;
	t_prompt		prompt;
	t_AST_SCRIPT	*script;
	t_fd			io_backup[IO_SIZE];
}	t_shell;

//@func
/*
** < script.c > */

void	shell_clear_script(t_shell *shell);
void	shell_replace_script(t_shell *shell, t_AST_SCRIPT *script);
void	shell_reconnect_io(t_shell *shell);
int		shell_exec_script(t_shell *shell);
/*
** < shell.c > */

t_res	shell_init(t_shell *shell, char *envp[]);
void	del_shell(t_shell *shell);
#endif