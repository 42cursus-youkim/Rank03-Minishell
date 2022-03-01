#include "minishell.h"

//	raw error message
t_res	error_msg_return(char *message[])
{
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED "minishell: ", NULL});
	ft_writes(STDERR_FILENO, message);
	ft_write(STDERR_FILENO, END "\n");
	return (ERR);
}

t_res	error_with_exitcode(char *message[], t_dict *env, int exitcode)
{
	env_set_exitcode(env, exitcode);
	return (error_msg_return(message));
}

t_res	error_msg_category(char *category, char *msg)
{
	error_msg_return((char *[]){
		category, ": ", msg, NULL});
	return (ERR);
}

t_res	error_msg_bad_opt(char *category, char *opt)
{
	if (!is_opt(opt))
		return (ERR);
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED "minishell: ", category, ": bad option: -", NULL});
	write(STDERR_FILENO, &opt[1], 1);
	return (ERR);
}

//	ex) bash: cd: dfsa: No such file or directory
t_res	error_syscall_with_arg(char *category, char *arg)
{
	error_msg_return((char *[]){
		category, ": ", arg, ": ", strerror(errno), NULL});
	return (ERR);
}
