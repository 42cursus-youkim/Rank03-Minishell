#ifndef PROMPT_H
# define PROMPT_H

typedef struct s_prompt
{
	char	*user;
	char	*ps1;
	char	*ps2;
}	t_prompt;

//@func
/*
** < prompt.c > */

void	prompt(void);
/*
** < util.c > */

bool	is_line_eof(char *line);
bool	is_line_empty(char *line);
void	prompt_init(t_prompt *prompt);
void	del_prompt(t_prompt *prompt);
/*
** < interrupt.c > */

void	prompt_new_line(int status);
void	prompt_replace_line(char *prompt, char *str);
#endif