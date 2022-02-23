#ifndef EXEC_H
# define EXEC_H

typedef struct s_context
{
	t_fd	io_input;
	t_fd	io_output;
	char	*executable;
	char	**argv;
	char	**env;
}	t_context;

//@func
/*
** < argv.c > */

char	**new_argv_from_cmd(char *executable, t_AST_COMMAND *cmd);
/*
** < exec.c > */

void	child_proc_exec(t_AST_COMMAND *cmd, t_shell *shell);
int		api_exec_cmd_at(t_shell *shell, int index);
/*
** < redirect.c > */

void	api_create_redirect(t_AST_NODE *redirect);
/*
** < util.c > */

bool	is_parent(pid_t pid);
bool	is_child(pid_t pid);
void	send_output_to_pipe(t_fd pipefd[PIPE_SIZE]);
void	receive_input_from_pipe(t_fd pipefd[PIPE_SIZE]);
#endif