#ifndef PROMPT_H
# define PROMPT_H

# define SIGN "\001"
# define EIGN "\002"

typedef struct s_prompt
{
	char	*user;
	char	*ps1;
	char	*ps2;
}	t_prompt;

//@func
/*
** < interrupt.c > */

void	prompt_ignore_signal(int status);
void	prompt_new_line(int status);
/*
** < prompt.c > */

void	prompt(t_dict *env);
/*
** < util.c > */

bool	is_line_eof(char *line);
bool	is_line_empty(char *line);
void	prompt_exit(char *line);
void	cursor_up(void);
void	prompt_replace_line_with(char *line, char *ps, char *new_line);
#endif