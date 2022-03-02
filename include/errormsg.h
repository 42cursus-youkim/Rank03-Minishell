/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormsg.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORMSG_H
# define ERRORMSG_H

//@func
/*
** < error.c > */

t_res	error_msg_return(char *message[]);
t_res	error_with_exitcode(char *message[], t_dict *env, int exitcode);
t_res	error_msg_category(char *category, char *msg);
t_res	error_msg_bad_opt(char *category, char *opt);
t_res	error_syscall_with_arg(char *category, char *arg);
#endif