#include "minishell.h"

static int	export_print(t_dict *env)
{
	int		id;
	t_ditem	*item;
	t_ditem	**items;

	items = new_dict_kv_ordered(env);
	id = -1;
	while (++id < env->size)
	{
		item = items[id];
		if (!item || !item->key)
			continue ;
		printf(BHYEL "declare -x %-s" END, item->key);
		if (item->value)
			printf("=" HGRN "%s" END, (char *)item->value);
		printf("\n");
	}
	free(items);
	return (EXIT_SUCCESS);
}

static int	export_variables(
	t_context *context, t_shell *shell, const int len)
{
	int			i;
	t_res		res;

	res = OK;
	i = 0;
	while (++i < len)
		res = env_set(shell->env, context->argv[i]);
	if (res != OK)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_context *context, t_shell *shell)
{
	const int	len = ft_arr_len(context->argv);

	if (check_no_opt(context->argv, "export") != OK)
		return (EXIT_FAILURE);
	if (len == 1)
		return (export_print(shell->env));
	else
		return (export_variables(context, shell, len));
}
