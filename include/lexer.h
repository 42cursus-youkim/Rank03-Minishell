/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	t_AST_type			type;
	char				*text;
	t_AST_expansion		**expansions;
}	t_token;

//@func
/*
** < lexer.c > */

t_token		*new_tokens_from_line(char *line, t_dict *env);
/*
** < tokenizer.c > */

char		*new_quotes_remove(const char *str);
t_token		*new_tokens_from_list(t_list *scan_list);
/*
** < util.c > */

t_AST_type	tokentype_check(t_scan_node *node);
void		tokens_print(t_token tokens[]);
void		del_tokens(t_token tokens[]);
#endif