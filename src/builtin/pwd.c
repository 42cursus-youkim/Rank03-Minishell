#include "minishell.h"

char	*new_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_syscall("getcwd");
		exit(EXIT_FAILURE);
	}
	return (cwd);
}

int	builtin_pwd(t_context *context, t_shell *shell)
{
	char	*cwd;

	(void)context;
	(void)shell;
	cwd = new_cwd();
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
