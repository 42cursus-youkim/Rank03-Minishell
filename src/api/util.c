#include "minishell.h"

bool	is_parent(pid_t pid)
{
	return (pid > 0);
}

bool	is_child(pid_t pid)
{
	return (pid == 0);
}
