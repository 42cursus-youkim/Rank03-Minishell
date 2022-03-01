#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

# include <stdbool.h>
# include <sys/types.h>

typedef enum e_procflag
{
	PIPE_READ = 0,
	PIPE_WRITE = 1,
	PIPE_SIZE = 2,
	INPUT = 0,
	OUTPUT = 1,
	IO_SIZE = 2,
}	t_procflag;

typedef enum e_exitcode
{
	EXIT_BUILTINS_ERR = 2,
	EXIT_COMMAND_NOT_IN_PATH = 127,
	EXIT_FATAL_ERR_CAUSED_BY_SIGNAL = 128,
	EXIT_EXIT_STATUS_OUT_OF_RANGE = 255,
	EXIT_CODE_RANGE = 256,
}	t_exitcode;

typedef int	t_fd;

#endif