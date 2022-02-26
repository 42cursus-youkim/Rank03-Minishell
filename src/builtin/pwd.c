#include "minishell.h"

static bool	has_error(char *argv[])
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (is_opt(argv[i]))
			printf(RED "pwd: bad option: -%c\n" END, argv[i][1]);
		else
			printf(RED "pwd: too many arguments\n" END);
		return (true);
	}
	return (false);
}

void	builtin_pwd(t_context *context, t_shell *shell)
{
	if (has_error(context->argv))
		return ;
	ft_writes(STDOUT_FILENO, (char *[]){
		env_get(shell->env, "PWD"), "\n", NULL});
}
