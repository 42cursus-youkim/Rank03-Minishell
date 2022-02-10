#include "minishell.h"

static void	signal_handler(int status)
{
	if (status == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
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
	while (true)
	{
		line = readline(prompt);
		if (!line || is_str_equal(line, "exit"))
		{
			printf("\r%sexit\n", prompt);
			break ;
		}
		else if (ft_strlen(line) > 0)
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
