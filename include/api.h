#ifndef API_H
# define API_H

typedef enum e_procflag
{
	PIPE_READ = 0,
	PIPE_WRITE = 1,
	INPUT = 0,
	OUTPUT = 1,
	TEMP = 1,
}	t_procflag;

typedef enum e_exitcode
{
	EXITCODE_OK = 0,
	EXITCODE_GENERAL_ERR = 1,
	EXITCODE_BUILTIN_ERR = 2,
	EXITCODE_CANNOT_EXECUTE_ERR = 126,
	EXITCODE_COMMAND_NOT_FOUND_ERR = 127,
	EXITCODE_INVALID_EXIT_ARG_ERR = 128,
	EXITCODE_FATAL_ERR_CAUSED_BY_SIGNAL = 128,
}	t_exitcode;

typedef struct s_context
{
	pid_t			pid;
	t_fd			infd;
	t_fd			outfd;
	t_dict			*env;
	t_AST_COMMAND	*cmd;
}	t_context;

//@func
/*
** < exec.c > */

t_res	api_exec_cmd(t_AST_COMMAND *cmd, t_dict *env);
/*
** < path.c > */

char	*new_path_resolved(char *path, t_dict *env);
char	**new_raw_path(t_dict *env);
char	**new_path(t_dict *env);
char	**new_path_with_name(t_dict *env, char *name);
/*
** < signal.c > */

int		api_handle_status(int status);
/*
** < util.c > */

bool	is_parent(pid_t pid);
bool	is_child(pid_t pid);
#endif