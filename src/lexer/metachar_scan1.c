#include "minishell.h"

static t_res	metastr_append_error(t_metastr *metastr, t_scan_data *data)
{
	error_with_exitcode((char *[]){BRED, MINISHELL, SYNTAX_ERROR,
		" `", metastr->str, "'\n", END, NULL}, data->env, 2);
	data->env_flag = true;
	return (free_arr_n_return((char *[]){
			metastr->prev, metastr->str, NULL}, ERR));
}

static t_res	metastr_append(
	t_list **list, t_metastr *metastr, char c, t_scan_data *data)
{
	t_list	*list_element;

	if (is_prev_metachar_attachable(metastr->prev))
	{
		if (list_element_create(&list_element, metastr->str, NULL) == ERR)
			return (free_arr_n_return(
					(char *[]){metastr->prev, metastr->str, NULL}, ERR));
		ft_list_append(list, list_element);
		if (!c)
			return (UNSET);
		free(metastr->prev);
		metastr->prev = metastr->str;
		metastr->str = new_str((char []){c, '\0'});
		if (!metastr->str)
			return (free_n_return(&metastr->prev, error_malloc_msg()));
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
		if (list_element_create(&list_element, metastr->str, NULL) == ERR)
			return (free_arr_n_return(
					(char *[]){metastr->prev, metastr->str, NULL}, ERR));
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
	if (metastr_init(&metastr, data->line[metastr.i]) == ERR)
		return (ERR);
	while (is_metachar(data->line[++metastr.i]) || !data->line[metastr.i])
	{
		res = metachar_attachable(
				&metastr.str, data->line[metastr.i - 1], data->line[metastr.i]);
		if (res == OK)
			continue ;
		if (res == ERR)
			return (free_n_return(&metastr.prev, ERR));
		res = metastr_append(
				list, &metastr, data->line[metastr.i], data);
		if (res == UNSET)
			break ;
		if (res == ERR)
			return (ERR);
	}
	return (metachar_last_check(list, data, &metastr));
}

t_res	metachar_scan(t_list **list, t_scan_data *data)
{
	if (is_metachar(data->line[data->idx])
		&& !is_quotes_open(NULL, data->buf))
	{
		if (buf_to_list(list, &data->buf) == ERR)
			return (ERR);
		if (metachar_valid_check(list, data) == ERR)
			return (free_n_return(&data->buf, ERR));
		return (OK);
	}
	return (UNSET);
}
