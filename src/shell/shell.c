#include "minishell.h"

static void	shell_increase_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl_num;

	shlvl_str = env_get(shell->env, "SHLVL");
	if (!shlvl_str || ft_atoi(shlvl_str, &shlvl_num) == ERR)
		shlvl_num = 1;
	shlvl_num++;
	shlvl_str = new_itoa(shlvl_num);
	if (shlvl_str)
		dict_set(shell->env, "SHLVL", shlvl_str);
}

t_res	shell_init(t_shell *shell, char *envp[])
{
	shell->env = new_env(envp);
	if (!shell->env)
		return (ERR);
	shell_increase_shlvl(shell);
	shell->script = NULL;
	shell->io_backup[INPUT] = api_dup(STDIN_FILENO);
	shell->io_backup[OUTPUT] = api_dup(STDOUT_FILENO);
	prompt_init(shell);
	return (OK);
}

void	del_shell(t_shell *shell)
{
	del_env(shell->env);
	del_prompt(&shell->prompt);
	shell_clear_script(shell);
	api_close_pipe(shell->io_backup);
}
