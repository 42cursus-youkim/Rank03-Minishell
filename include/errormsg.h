#ifndef ERRORMSG_H
# define ERRORMSG_H

//@func
/*
** < error.c > */

t_res	error_msg_return(char *message[]);
t_res	error_malloc_msg(void);
t_res	error_with_exitcode(char *message[], t_dict *env, int exitcode);
t_res	error_msg_bad_opt(char *category, char *opt);
#endif