#include "minishell.h"

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