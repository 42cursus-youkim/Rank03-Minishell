#ifndef OPEN_H
# define OPEN_H

//@func
/*
** < file.c > */

bool	is_dir(char *path);
bool	is_path(char *path);
bool	is_executable_exists(char *file, t_dict *env);
char	*new_executable_from_env(char *file, t_dict *env);
/*
** < heredoc.c > */

t_fd	shell_heredoc(t_shell *shell, const char *eof);
/*
** < open.c > */

t_fd	api_open(char *file, int flag);
t_fd	api_open_redirect_input(t_AST_NODE *redirect, t_shell *shell);
t_res	api_open_redirect_output(t_AST_NODE *redirect);
/*
** < redirect.c > */

void	cmd_try_open_redirect( t_AST_NODE *redirect, t_AST_COMMAND *cmd,
			t_shell *shell);
void	cmd_open_redirects(t_AST_COMMAND *cmd, t_shell *shell);
void	shell_open_redirects(t_shell *shell);
/*
** < util.c > */

bool	is_redirect_input(t_redirect_op op);
bool	is_redirect_output(t_redirect_op op);
#endif