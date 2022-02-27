#include "minishell.h"

static char	*prompt_color_result(t_shell *shell)
{
	static char	*colors[2] = {BRED, BBLU};
	char		*color;

	color = colors[shell->env->exitcode == OK];
	return (new_str_join((char *[]){
			BBLU, shell->prompt.user, "@minishell ",
			color, "> " END, NULL}, '\0'));
}

void	prompt_refresh_ps(t_shell *shell)
{
	shell->prompt.user = env_get(shell->env, "USER");
	ft_str_replace(&shell->prompt.ps1, prompt_color_result(shell));
}
