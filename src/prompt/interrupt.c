#include "minishell.h"

/*
	- printf: move to new line
	- rl_on_new_line: Regenerate the prompt on a newline
	- rl_replace_line: Clear the previous text
*/
static void	prompt_spawn_new_line(int status)
{
	(void)status;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	prompt_handle_signal(void)
{
	signal(SIGINT, prompt_spawn_new_line);
	signal(SIGQUIT, SIG_IGN);
}

void	prompt_ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
