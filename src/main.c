#include "minishell.h"
#define BACKSPACE "\b \b"

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

bool	is_line_eof(char *line)
{
	return (line == NULL);
}

bool	is_line_empty(char *line)
{
	return (ft_strlen(line) > 0);
}

void	prompt(void)
{
	char	*line;
	char	*prompt;
	char	*name;

	name = getenv("USER");
	prompt = new_str_join((char *[]){
			BGRN, name, "@🐚 > " END, NULL}, '\0');
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
			rl_redisplay();
			printf("typed <%s>\n", line);
		}
		free(line);
	}
}

int	main(void)
{
	signal(SIGINT, signal_handler);
	prompt();
	return (0);
}
