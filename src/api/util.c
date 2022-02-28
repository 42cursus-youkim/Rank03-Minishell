#include "minishell.h"

//	frees allocated memory from shell && exits with exitcode
void	api_exit(t_shell *shell, int exitcode)
{
	del_shell(shell);
	exit(exitcode);
}

void	api_sleep(size_t tick)
{
	size_t	i;

	i = -1;
	while (++i < tick * 1000)
		;
}

void	api_show_logo(char *file)
{
	t_fd	fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == ERR)
		return ;
	while (true)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		printf(BBLU "%s" END, line);
		api_sleep(40000);
		free(line);
	}
}
