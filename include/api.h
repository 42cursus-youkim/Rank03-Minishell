#ifndef API_H
# define API_H

typedef enum e_exitcode
{
	EXIT_BUILTINS_ERR = 2,
	EXIT_COMMAND_NOT_IN_PATH = 127,
	EXIT_FATAL_ERR_CAUSED_BY_SIGNAL = 128,
}	t_exitcode;

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
** < file.c > */

bool	is_dir(char *path);
bool	is_path(char *path);
bool	is_executable_exists(char *file, t_dict *env);
char	*new_executable_from_env(char *file, t_dict *env);
/*
** < heredoc.c > */

t_fd	shell_heredoc(t_shell *shell, const char *eof);
/*
** < path.c > */

char	**new_names_from_path(char *name, t_dict *env);
/*
** < redirect.c > */

t_res	api_open(t_fd *fd_p, t_AST_NODE *redirect, t_shell *shell);
void	cmd_try_open_redirect( t_AST_NODE *node, t_AST_COMMAND *cmd,
			t_shell *shell);
void	cmd_open_redirects(t_AST_COMMAND *cmd, t_shell *shell);
void	shell_open_redirects(t_shell *shell);
/*
** < signal.c > */

int		api_handle_status(int status);
/*
** < util.c > */

void	api_exit(t_shell *shell, int exitcode);
void	api_sleep(size_t tick);
void	api_show_logo(char *file);
#endif