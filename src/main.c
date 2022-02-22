#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell_init(&shell, envp);
	shell_prompt(&shell);
	del_shell(&shell);
	return (0);
}
