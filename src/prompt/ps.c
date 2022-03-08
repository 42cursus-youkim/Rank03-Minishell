#include "minishell.h"

static char	*new_error_code_colored(t_shell *shell)
{
	const int	exitcode = shell->env->exitcode;

	return (new_str_join_freed("", 3, (t_tempstr []){
			{REDHB BYEL, 0},
			{new_itoa(exitcode), 1},
			{END, 0},
		}));
}

static char	*new_prompt_with_result(t_shell *shell)
{
	const int	exitcode = shell->env->exitcode;
	char		*new;

	new = new_str_join((char *[]){
			BBLU, shell->prompt.user, "@minishell ", NULL}, '\0');
	if (exitcode == OK)
		ft_str_extend(&new, "> " END);
	if (exitcode > EXIT_FAILURE)
		ft_str_extend_freed(&new, new_error_code_colored(shell));
	if (exitcode >= EXIT_FAILURE)
		ft_str_extend(&new, BRED "> " END);
	return (new);
}

void	prompt_refresh_ps(t_shell *shell)
{
	shell->prompt.user = env_get(shell->env, USER);
	ft_str_replace(&shell->prompt.ps1, new_prompt_with_result(shell));
}
