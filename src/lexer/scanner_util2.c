#include "minishell.h"

static t_res	metachar_attachable(char **pstr, char prev_c, char c)
{
	if (prev_c != '|' && ft_strlen(*pstr) == 1 && c == prev_c)
	{
		ft_str_append(pstr, c);
		return (OK);
	}
	return (ERR);
}

static bool	is_prev_metachar_attachable(char *str)
{
	return (is_str_equal(str, "") || is_str_equal(str, "|"));
}

static t_res	metastr_append(
	t_list **list, char **prev_pstr, char **pstr, char c)
{
	if (is_prev_metachar_attachable(*prev_pstr))
	{
		ft_list_append(list, new_list(new_scan_node(new_str(*pstr), NULL)));
		if (!c)
			return (UNSET);
		free(*prev_pstr);
		*prev_pstr = *pstr;
		*pstr = new_str((char []){c, '\0'});
		return (OK);
	}
	else
	{
		printf(BRED "minishell: syntax error near unexpected token");
		printf(" `%s'\n" END, *pstr);
		free(*prev_pstr);
		free(*pstr);
		return (ERR);
	}
}

static bool	is_metachar_valid(t_list **list, char *str, int *idx)
{
	char	*metastr;
	char	*prev_metastr;
	int		i;
	t_res	res;

	i = *idx;
	metastr = new_str((char []){str[i], '\0'});
	prev_metastr = new_str("");
	while (is_metachar(str[++i]) || !str[i])
	{
		if (metachar_attachable(&metastr, str[i - 1], str[i]) == OK)
			continue ;
		res = metastr_append(list, &prev_metastr, &metastr, str[i]);
		if (res == UNSET)
			break ;
		if (res == ERR)
			return (false);
	}
	if (str[i] && is_prev_metachar_attachable(prev_metastr))
		ft_list_append(list, new_list(new_scan_node(new_str(metastr), NULL)));
	*idx = --i;
	free(metastr);
	free(prev_metastr);
	return (true);
}

t_res	metachar_scan(t_list **list, char **buf, char *str, int *idx)
{
	if (is_metachar(str[*idx]) && !is_quotes_open(NULL, *buf))
	{
		buf_to_list(list, buf);
		if (!is_metachar_valid(list, str, idx))
			return (ERR);
		return (OK);
	}
	return (UNSET);
}
