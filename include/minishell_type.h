#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

typedef enum e_procflag
{
	PIPE_READ = 0,
	PIPE_WRITE = 1,
	PIPE_SIZE = 2,
	INPUT = 0,
	OUTPUT = 1,
	IO_SIZE = 2,
}	t_procflag;

#endif