#ifndef PIPE_H
# define PIPE_H

typedef struct s_pipe_context
{
	int			*pids;
	t_fd		prev[PIPE_SIZE];
	t_fd		next[PIPE_SIZE];
}	t_pipe_context;

//@func
/*
** < pipe.c > */

int		api_exec_pipe(t_shell *shell);
/*
** < send.c > */

void	api_send_output_to_pipe(t_fd pipefd[PIPE_SIZE]);
void	api_receive_input_from_pipe(t_fd pipefd[PIPE_SIZE]);
/*
** < status.c > */

bool	has_pipe_prev(int index);
bool	has_pipe_next(int index, int length);
/*
** < util.c > */

t_res	api_create_pipe(t_fd pipefd[PIPE_SIZE]);
void	api_copy_pipe(t_fd from[PIPE_SIZE], t_fd to[PIPE_SIZE]);
void	api_close_pipe(t_fd pipefd[PIPE_SIZE]);
int		wait_pipe_processes(int pids[], const int len);
#endif