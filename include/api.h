#ifndef API_H
# define API_H

typedef enum e_procflag
{
	PIPE_READ = 0,
	PIPE_WRITE = 1,
	INPUT = 0,
	OUTPUT = 1,
	TEMP = 1,
	WAIT_CHILD_END = 0,
}	t_procflag;

typedef enum e_exitcode
{
	EXITCODE_OK = 0,
	EXITCODE_GENERAL_ERR = 1,
	EXITCODE_BUILTIN_ERR = 2,
	EXITCODE_FATAL_ERR_CAUSED_BY_SIGNAL = 128,
}	t_exitcode;

//@func
/*
** < exec.c > */

void	api_raw_exec(char *argv[], t_dict *env);
t_res	api_exec_cmd(char **argv);
/*
** < file.c > */

t_res	api_open(t_fd *fd_p, t_AST_NODE *redirect);
/*
** < path.c > */

char	*new_path_resolved(char *path, t_dict *env);
char	**new_raw_path(t_dict *env);
char	**new_path(t_dict *env);
char	**new_path_with_name(t_dict *env, char *name);
/*
** < pipe.c > */

t_res	api_exec_pipe(int size, char **argvs[]);
/*
** < redirect.c > */

void	redirect_output(t_AST_NODE *redirect);
void	redirect_input(t_AST_NODE *redirect);
void	api_redirect(t_AST_NODE *redirect);
/*
** < signal.c > */

int		api_handle_status(int status);
/*
** < util.c > */

bool	is_parent(pid_t pid);
bool	is_child(pid_t pid);
void	send_output_to_pipe(t_fd pipefd[2]);
void	receive_input_from_pipe(t_fd pipefd[2]);
#endif