#include "minishell.h"

static t_res	metastr_append(
	t_list **list, char **prev_pstr, char **pstr, char c)
{
	t_list	*list_element;

	if (is_prev_metachar_attachable(*prev_pstr))
	{
		if (list_element_create(&list_element, *pstr, NULL) == ERR)
			return (free_arr_n_return(
					(char *[]){*prev_pstr, *pstr, NULL}, ERR));
		ft_list_append(list, list_element);
		if (!c)
			return (UNSET);
		free(*prev_pstr);
		*prev_pstr = *pstr;
		*pstr = new_str((char []){c, '\0'});
		if (!*pstr)
			return (free_n_return(prev_pstr,
					error_msg_return(MALLOC_ERROR_MSG)));
		return (OK);
	}
	else
	{
		return (free_arr_n_return((char *[]){*prev_pstr, *pstr, NULL},
			error_msg_return((char *[]){
				MINISHELL, SYNTAX_ERROR, " `", *pstr, "'\n", END, NULL})));
	}
}

static t_res	metachar_last_check(
	t_list **list, char *str, int *idx, t_metastr *metastr)
{
	t_list	*list_element;

	if (str[metastr->i] && is_prev_metachar_attachable(metastr->prev))
	{
		if (list_element_create(&list_element, metastr->str, NULL) == ERR)
			return (free_arr_n_return(
					(char *[]){metastr->prev, metastr->str, NULL}, ERR));
		ft_list_append(list, list_element);
	}
	*idx = --(metastr->i);
	free(metastr->str);
	free(metastr->prev);
	return (OK);
}

static t_res	metachar_valid_check(t_list **list, char *str, int *idx)
{
	t_metastr	metastr;
	t_res		res;

	metastr.i = *idx;
	if (metastr_init(&metastr, str[metastr.i]) == ERR)
		return (ERR);
	while (is_metachar(str[++metastr.i]) || !str[metastr.i])
	{
		res = metachar_attachable(
				&metastr.str, str[metastr.i - 1], str[metastr.i]);
		if (res == OK)
			continue ;
		if (res == ERR)
			return (free_n_return(&metastr.prev, ERR));
		res = metastr_append(list, &metastr.prev, &metastr.str, str[metastr.i]);
		if (res == UNSET)
			break ;
		if (res == ERR)
			return (ERR);
	}
	return (metachar_last_check(list, str, idx, &metastr));
}

t_res	metachar_scan(t_list **list, char **buf, char *str, int *idx)
{
	if (is_metachar(str[*idx]) && !is_quotes_open(NULL, *buf))
	{
		if (buf_to_list(list, buf) == ERR)
			return (ERR);
		if (metachar_valid_check(list, str, idx) == ERR)
			return (ERR);
		return (OK);
	}
	return (UNSET);
}
