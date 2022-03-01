#include "minishell.h"

static t_res	metastr_append_error(t_metastr *metastr, t_scan_data *data)
{
	error_with_exitcode((char *[]){SYNTAX_ERROR,
		" `", metastr->str, "'", NULL}, data->env, 2);
	return (free_arr_n_return((char *[]){
			metastr->prev, metastr->str, NULL}, ERR));
}

static t_res	metastr_append(
	t_list **list, t_metastr *metastr, char c, t_scan_data *data)
{
	t_list	*list_element;

	if (is_prev_metachar_attachable(metastr->prev))
	{
		list_element_create(&list_element, metastr->str, NULL);
		ft_list_append(list, list_element);
		if (!c)
			return (UNSET);
		free(metastr->prev);
		metastr->prev = metastr->str;
		metastr->str = new_str((char []){c, '\0'});
		return (OK);
	}
	else
		return (metastr_append_error(metastr, data));
}

static t_res	metachar_last_check(
	t_list **list, t_scan_data *data, t_metastr *metastr)
{
	t_list	*list_element;

	if (data->line[metastr->i] && is_prev_metachar_attachable(metastr->prev))
	{
		list_element_create(&list_element, metastr->str, NULL);
		ft_list_append(list, list_element);
	}
	data->idx = --(metastr->i);
	free(metastr->str);
	free(metastr->prev);
	return (OK);
}

static t_res	metachar_valid_check(t_list **list, t_scan_data *data)
{
	t_metastr	metastr;
	t_res		res;

	metastr.i = data->idx;
	metastr.str = new_str((char []){data->line[metastr.i], '\0'});
	metastr.prev = new_str("");
	while (is_metachar(data->line[++metastr.i]) || !data->line[metastr.i])
	{
		if (is_metachar_attachable(&metastr.str,
				data->line[metastr.i - 1], data->line[metastr.i]))
			continue ;
		res = metastr_append(list, &metastr, data->line[metastr.i], data);
		if (res == UNSET)
			break ;
		if (res == ERR)
			return (ERR);
	}
	return (metachar_last_check(list, data, &metastr));
}

/*
	scan if `|, <, >` is a valid combination of pipeline and redirections
	- UNSET: just character in quotes string
	- ERR: syntax error
*/
t_res	metachar_scan(t_list **list, t_scan_data *data)
{
	if (is_metachar(data->line[data->idx])
		&& !is_quotes_open(NULL, data->buf, QUOTE_CLOSE, '\0'))
	{
		buf_to_list(list, &data->buf);
		if (metachar_valid_check(list, data) == ERR)
			return (free_n_return(data->buf, ERR));
		return (OK);
	}
	return (UNSET);
}
