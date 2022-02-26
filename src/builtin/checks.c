#include "minishell.h"

t_res	check_no_opt(char *argv[], char *category)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (is_opt(argv[i]))
			return (error_msg_bad_opt(category, argv[i]));
	return (OK);
}

//	max does not include argv[0]
t_res	check_arg_no_more_than(
	char *argv[], char *category, int max)
{
	if (ft_arr_len(argv) > max + 1)
		return (error_msg_category(category, "too many arguments"));
	return (OK);
}

t_res	check_no_opt_arg(char *argv[], char *category)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (is_opt(argv[i]))
			return (error_msg_bad_opt(category, argv[i]));
		else
			return (error_msg_category(category, "too many arguments"));
	}
	return (OK);
}
