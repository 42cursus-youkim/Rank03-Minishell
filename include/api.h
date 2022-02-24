#ifndef API_H
# define API_H

typedef enum e_procflag
{
	PIPE_READ = 0,
	PIPE_WRITE = 1,
	PIPE_SIZE = 2,
	INPUT = 0,
	OUTPUT = 1,
	TEMP = 1,
	WAIT_UNTIL_CHILD_END = 0,
}	t_procflag;

typedef enum e_exitcode
{
	EXIT_BUILTIN_ERR = 2,
	EXIT_FATAL_ERR_CAUSED_BY_SIGNAL = 128,
}	t_exitcode;

//@func
/*
** < file.c > */

t_res	api_open(t_fd *fd_p, t_AST_NODE *redirect);
bool	is_file_exists(char *filename);
bool	is_executable_exists(char *file, t_dict *env);
char	*new_executable_from_env(char *file, t_dict *env);
/*
** < heredoc.c > */

t_fd	shell_heredoc(t_shell *shell, char *eof);
/*
** < path.c > */

char	**new_names_from_path(char *name, t_dict *env);
/*
** < redirect.c > */

void	api_create_redirect(t_AST_NODE *redirect);
/*
** < shell.c > */

void	shell_clear_script(t_shell *shell);
void	shell_replace_script(t_shell *shell, t_AST_SCRIPT *script);
void	shell_init(t_shell *shell, char *envp[]);
void	del_shell(t_shell *shell);
void	api_exit(t_shell *shell, int exitcode);
/*
** < signal.c > */

int		api_handle_status(int status);
#endif