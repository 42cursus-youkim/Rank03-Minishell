#include "minishell.h"

static int	api_handle_signaled_status(int status)
{
	const int	sig = WTERMSIG(status);

	if (sig == SIGQUIT)
		ft_write(1, HRED "QUIT: 3\n" END);
	printf("returns 128 + %d\n", sig);
	return (EXIT_FATAL_ERR_CAUSED_BY_SIGNAL + sig);
}

int	api_handle_status(int status)
{
	if (DEBUG)
		printf(BLUHB BWHT "|exit?|sig? | sig |" END
			"\n|%-16s|%-16s| %-3d |\n",
			ft_bool_to_str(WIFEXITED(status)),
			ft_bool_to_str(WIFSIGNALED(status)),
			WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (api_handle_signaled_status(status));
	else
		return (EXIT_FAILURE);
}
