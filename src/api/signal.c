#include "minishell.h"

static int	api_handle_signaled_status(int status)
{
	const int	sig = WTERMSIG(status);

	if (sig == SIGQUIT)
		ft_write(1, HRED "QUIT: 3\n" END);
	printf("returns 128 + %d\n", sig);
	return (EXIT_FATAL_ERR_CAUSED_BY_SIGNAL + sig);
}

char	*bool_to_str(bool b)
{
	static char	*value[] = {
		BRED "false" END,
		HGRN "true" END};

	return (value[b]);
}

int	api_handle_status(int status)
{
	printf("WIFEXITED(status): %s\n", bool_to_str(WIFEXITED(status)));
	printf("WIFSIGNALED(status): %s\n", bool_to_str(WIFSIGNALED(status)));
	printf("WTERMSIG(status): %s\n", bool_to_str(WTERMSIG(status)));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (api_handle_signaled_status(status));
	else
		return (EXIT_FAILURE);
}
