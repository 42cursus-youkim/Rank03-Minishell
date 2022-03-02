/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojekim  <hyojekim@student.42seoul.k      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:16:52 by hyojekim          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:52 by hyojekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

typedef enum e_scanner_type
{
	CMD = 0,
	HEREDOC,
}	t_scanner_type;

typedef enum e_quote_status
{
	QUOTE_CLOSE = 0,
	QUOTE_OPEN = 1,
}	t_quote_status;

typedef struct s_scan_data
{
	char			*buf;
	char			*line;
	int				idx;
	t_dict			*env;
	t_scanner_type	type;
}	t_scan_data;

typedef struct s_expansion_scan_info
{
	t_scan_data		*data;
	int				start_i;
	t_AST_expansion	**expansions;
	int				begin;
	int				end;

}	t_expansion_scan_info;

typedef struct s_metastr
{
	char	*str;
	char	*prev;
	int		i;
}	t_metastr;

typedef struct s_scan_node
{
	char				*text;
	t_AST_expansion		**expansions;
}	t_scan_node;

//@func
/*
** < dollar_scan1.c > */

t_res		dollar_scan(t_list **list, t_scan_data *data);
/*
** < dollar_scan2.c > */

t_res		expansions_update_with_brace( t_expansion_scan_info *info, int end,
				bool brace);
t_res		expansion_location_init(t_expansion_scan_info *info, int *i);
bool		is_multi_expansions(t_expansion_scan_info info, int i);
/*
** < expansion.c > */

int			expansions_len(t_AST_expansion *expansions[]);
t_res		expansions_append(t_AST_expansion **parr[],
				t_AST_expansion *element);
t_res		expansions_append_free( t_AST_expansion **parr[],
				t_AST_expansion *element);
void		expansions_print(t_AST_expansion *expansions[]);
/*
** < metachar_scan1.c > */

t_res		metachar_scan(t_list **list, t_scan_data *data);
/*
** < metachar_scan2.c > */

bool		is_metachar_attachable(char **pstr, char prev_c, char c);
bool		is_prev_metachar_attachable(char *str);
/*
** < scanner.c > */

t_res		scanner(t_list **scan_list, char *line, t_dict *env);
/*
** < scanner_list.c > */

t_scan_node	*new_scan_node(char *str, t_AST_expansion **arr);
void		del_scan_node(void *param);
void		scan_node_print(void *param);
/*
** < util.c > */

bool		is_quotes_open( char *last_quote, char *str, t_quote_status status,
				char init_quote);
bool		is_brace_open(char *str);
t_res		list_element_create( t_list **element, char *buf,
				t_AST_expansion **expansions);
t_res		buf_to_list(t_list **list, char **buf);
t_res		whitespace_scan(t_list **list, t_scan_data *data);
/*
** < util2.c > */

bool		is_metachar(char c);
bool		is_quotechar(char c);
bool		is_tilde_expansion(t_scan_data *data, int i);
/*
** < util3.c > */

bool		is_1stchar_valid(char c);
bool		is_variable_char_valid(char c);
bool		is_scan_continuos(char *buf, char c, t_scanner_type type);
t_res		free_n_return(void *data, t_res result);
t_res		free_arr_n_return(char *arr[], t_res result);
#endif