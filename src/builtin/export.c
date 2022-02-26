#include "minishell.h"

void	builtin_export(t_dict *env)
{
	ft_writes(STDOUT_FILENO, (char *[]){
		env_get(env, "PWD"), "\n", NULL});
}
