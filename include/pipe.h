#ifndef PIPE_H
# define PIPE_H

# include "error.h"
# include "shell.h"

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

void	api_copy_pipe(t_fd from[PIPE_SIZE], t_fd to[PIPE_SIZE]);
void	api_close_pipe(t_fd pipefd[PIPE_SIZE]);
t_fd	api_dup2(t_fd from, t_fd to);
t_fd	api_dup(t_fd from);
#endif