#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

typedef int	t_fd;

typedef struct s_prompt
{
	char	*user;
	char	*ps1;
	char	*ps2;
	char	*line;
}	t_prompt;

typedef struct s_shell
{
	t_dict			*env;
	t_prompt		prompt;
	t_AST_SCRIPT	*script;
}	t_shell;

#endif