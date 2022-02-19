#include "minishell.h"

static int	api_handle_signaled_status(int status)
{
	const int	sig = WTERMSIG(status);

	if (sig == SIGQUIT)
		ft_write(1, HRED "QUIT: 3\n" END);
	return (EXITCODE_FATAL_ERR_CAUSED_BY_SIGNAL + sig);
}

int	api_handle_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (api_handle_signaled_status(status));
	else
		return (EXITCODE_GENERAL_ERR);
}
