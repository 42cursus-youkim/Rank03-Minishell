#ifndef PROMPT_H
# define PROMPT_H

//@func
/*
** < interrupt.c > */

void	signal_handler(int status);
/*
** < prompt.c > */

void	prompt(void);
/*
** < util.c > */

bool	is_line_eof(char *line);
bool	is_line_empty(char *line);
#endif