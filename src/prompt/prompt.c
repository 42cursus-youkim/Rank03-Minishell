#include "minishell.h"

void	prompt(void)
{
	char		*line;
	t_prompt	prompt;

	prompt_init(&prompt);
	while (true)
	{
		line = readline(prompt.ps1);
		if (is_line_eof(line) || is_str_equal(line, "exit"))
		{
			prompt_replace_line(prompt.ps1, "exit");
			break ;
		}
		else if (!is_line_empty(line))
		{
			add_history(line);
			printf("typed <%s>; TODO: do something here\n", line);
		}
		free(line);
	}
	del_prompt(&prompt);
}
