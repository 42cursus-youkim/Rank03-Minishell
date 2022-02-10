#include "minishell.h"

/*
	- printf: move to new line
	- rl_on_new_line: Regenerate the prompt on a newline
	- rl_replace_line: Clear the previous text
*/
static void	signal_handler(int status)
{
	if (status == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	prompt(void)
{
	char	*line;
	char	*prompt;
	char	*name;

	name = getenv("USER");
	prompt = new_str_join((char *[]){
			BGRN, name, "@🐚 > " END, NULL}, '\0');
	signal(SIGINT, signal_handler);
	while (true)
	{
		line = readline(prompt);
		if (is_line_eof(line) || is_str_equal(line, "exit"))
		{
			printf("\r%sexit\n", prompt);
			break ;
		}
		else if (is_line_empty(line))
		{
			add_history(line);
			printf("typed <%s>\n", line);
		}
		free(line);
	}
}