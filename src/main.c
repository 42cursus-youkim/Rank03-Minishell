#include "minishell.h"

int	main(void) {
	// int		fd;
	// char	*line;

	// fd = open("logo.txt", O_RDONLY);
	// while (get_next_line(fd, &line) > 0)
	// {
	// 	printf("%s\n", line);
	// 	free(line);
	// }
	// free(line);     
	printf("%s\n", ft_strdup("hello world!"));
	printf("%d\n", ft_strlen("hello world!"));
	return (0);
}