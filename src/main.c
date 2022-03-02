#include "minishell.h"

static int	minishell(char *envp[])
{
	t_shell	shell;

	api_show_logo("logo.txt");
	if (shell_init(&shell, envp) == ERR)
		return (EXIT_FAILURE);
	shell_prompt(&shell);
	del_shell(&shell);
	return (0);
}

static int	test(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*line;
	t_shell	shell;

	if (argc == 1 || shell_init(&shell, envp) == ERR)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < argc)
	{
		line = new_str(argv[i]);
		shell_process_line(line, &shell);
		shell_run_line(&shell);
	}
	del_shell(&shell);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)minishell;

	return (test(argc, argv, envp));
	// return (minishell(envp));
}
