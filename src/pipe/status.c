#include <stdbool.h>

bool	has_pipe_prev(int index)
{
	return (index > 0);
}

bool	has_pipe_next(int index, int length)
{
	return (index < length - 1);
}