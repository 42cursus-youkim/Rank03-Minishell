/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# define	INDENT_SIZE 2

//@func
/*
** < repr1.c > */

void	ast_node_repr(t_AST_NODE *node, int level);
/*
** < repr2.c > */

void	ast_command_repr(t_AST_COMMAND *cmd, int level);
void	ast_pipeline_repr(t_AST_SCRIPT *pipeline, int level);
void	ast_script_repr(t_AST_SCRIPT *script);
#endif