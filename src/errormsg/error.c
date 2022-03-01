#include "minishell.h"

t_res	error_msg_return(char *message[])
{
	const int	len = ft_arr_len(message);
	int			i;

	i = -1;
	while (++i < len)
		ft_write(STDERR_FILENO, message[i]);
	return (ERR);
}

t_res	error_with_exitcode(char *message[], t_dict *env, int exitcode)
{
	env_set_exitcode(env, exitcode);
	return (error_msg_return(message));
}

t_res	error_msg_category(char *category, char *msg)
{
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED, "minishell: ", category, ": ", msg, END "\n", NULL});
	return (ERR);
}

t_res	error_msg_bad_opt(char *category, char *opt)
{
	if (!is_opt(opt))
		return (ERR);
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED, category, ": bad option: -", NULL});
	write(STDERR_FILENO, &opt[1], 1);
	ft_write(STDERR_FILENO, END "\n");
	return (ERR);
}

//	ex) bash: cd: dfsa: No such file or directory
t_res	error_syscall_with_arg(char *category, char *arg)
{
	ft_writes(STDERR_FILENO, (char *[]){BHRED,
		"minishell: ", category, ": ", arg, ": ", strerror(errno),
		END "\n", NULL});
	return (ERR);
}
