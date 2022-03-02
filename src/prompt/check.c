#include "minishell.h"

bool	is_line_eof(char *line)
{
	return (line == NULL);
}

bool	is_line_empty(char *line)
{
	return (ft_strlen(line) <= 0);
}
