#include "minishell.h"
	// int		fd;

	// fd = open("logo.txt", O_RDONLY);
	// while (get_next_line(fd, &line) > 0)
	// {
	// 	printf("%s\n", line);
	// 	free(line);
	// }
	// free(line);
	// char *str = ft_strdup("hello!");
	// ft_strappend(&str, "world!");
	// printf("%s\n", str);
	// free(str);
	// return (0);

void	minishell(void)
{
	char	*line;
	char	**arr;
	char prompt[128];
	char *name = getenv("USER");
	char *new;

	while (true)
	{
		sprintf(prompt, "%s%s@🐚 > %s", BGRN, name, END);
		line = readline(prompt);
		if (!line || is_str_equel(line, "exit"))
		{
			printf("\r%sexit\n", prompt);
			break ;
		}
		else if (ft_strlen(line) > 0)
		{
			add_history(line);
			arr = new_str_split(line, ' ');
			new = new_str_join(arr, ' ');
			printf("splitted then joined again: %s\n", new);
		}
		free(line);
	}
}
			// printf("typed\n");
			// for (int i = 0; arr[i]; i++)
			// 	printf("%s\n", arr[i]);



int	main(void) {
	minishell();
	// char **arr = ft_split("mary had a little lamb", ' ');
	// char *new = ft_arr_join(arr, '-');
	// printf("%s\n", new);
	// ft_arr_free(arr);
	// free(new);
	return (0);
}
