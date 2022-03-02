#ifndef PROMPT_H
# define PROMPT_H

typedef void(*t_sigfunc_f)(int);

//@func
/*
** < check.c > */

bool	is_line_eof(char *line);
bool	is_line_empty(char *line);
/*
** < interrupt.c > */

void	prompt_handle_signal(void);
void	prompt_ignore_signal(void);
void	child_handle_signal(void);
/*
** < prompt.c > */

void	prompt_init(t_shell *shell);
void	del_prompt(t_prompt *prompt);
void	shell_process_line(char *line, t_shell *shell);
void	shell_run_line(t_shell *shell);
void	shell_prompt(t_shell *shell);
/*
** < ps.c > */

void	prompt_refresh_ps(t_shell *shell);
/*
** < util.c > */

void	prompt_exit(t_shell *shell);
void	cursor_up(void);
void	prompt_eof_heredoc(t_shell *shell);
void	prompt_replace_line_with(char *line, char *ps, char *new_line);
#endif