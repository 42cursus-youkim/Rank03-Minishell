#include "minishell.h"

void	prompt(void)
{
	char		*line;
	char		*prompt;
	const char	*name = getenv("USER");

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
	prompt();
	return (0);
}
