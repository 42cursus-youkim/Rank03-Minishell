#ifndef API_H
# define API_H

typedef enum e_procflag
{
	CHILD = 0,
	PIPE_READ = 0,
	PIPE_WRITE = 1,
	INPUT = 0,
	OUTPUT = 1,
	TEMP = 1,
}	t_procflag;

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

bool	is_parent(pid_t pid);
void	api_exec_cmd(t_AST_COMMAND *cmd, t_dict *env);
/*
** < path.c > */

char	*new_path_resolved(char *path, t_dict *env);
char	**new_raw_path(t_dict *env);
char	**new_path(t_dict *env);
char	**new_path_with_name(t_dict *env, char *name);
#endif