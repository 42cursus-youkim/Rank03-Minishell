#include "minishell.h"

int	main(void) {
	int		fd;
	char	*line;

	fd = open("logo.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
	return (0);
}