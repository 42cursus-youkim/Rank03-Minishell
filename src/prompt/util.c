#include "minishell.h"

bool	is_line_eof(char *line)
{
	return (line == NULL);
}

bool	is_line_empty(char *line)
{
	return (ft_strlen(line) <= 0);
}

void	prompt_init(t_prompt *prompt)
{
	rl_catch_signals = 0;
	signal(SIGINT, prompt_new_line);
	prompt->user = getenv("USER");
	prompt->ps1 = new_str_join((char *[]){
			BGRN, prompt->user, "@🐚 > " END, NULL}, '\0');
	prompt->ps2 = new_str("🐚 > ");
}

/*
	- prompt: not freed; uses static allocation (init)
	- user: stores result of getenv(); should not be freed
	- ps1, ps2: freed
*/
void	del_prompt(t_prompt *prompt)
{
	free(prompt->ps1);
	free(prompt->ps2);
}