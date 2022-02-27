#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (shell_init(&shell, envp) == ERR)
		return (EXIT_FAILURE);
	shell_prompt(&shell);
	del_shell(&shell);
	return (0);
}
