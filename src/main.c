#include "minishell.h"
#define BACKSPACE "\b \b"

int	main(void)
{
	signal(SIGINT, signal_handler);
	prompt();
	return (0);
}
