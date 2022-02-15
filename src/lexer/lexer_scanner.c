#include "minishell.h"

t_res	buf_to_arr(char **parr[], char **buf)
{
	const int	buf_len = ft_strlen(*buf);

	if (buf_len == 0)
		return (UNSET);
	ft_arr_append(parr, *buf);
	free(*buf);
	*buf = new_str("");
	return (OK);
}

t_res	whitespace_scan(char **arr[], char **buf, char *str, int *idx)
{
	int	i;

	i = *idx;
	if (is_whitespace(str[i]) && !is_quotes_open(*buf))
	{
		buf_to_arr(arr, buf);
		while (is_whitespace(str[++i]))
			;
		*idx = --i;
		return (OK);
	}
	return (UNSET);
}

static bool	is_metachar_valid(char **arr[], char *str, int *idx)
{
	char		*metastr;
	char		*prev_metastr;
	int			i;

	i = *idx;
	metastr = new_str((char []){str[i], '\0'});
	prev_metastr = new_str("");
	while (is_metachar(str[++i]) || !str[i])
	{
		if (str[i - 1] != '|' && ft_strlen(metastr) == 1
			&& str[i] == str[i - 1])
		{
			ft_str_append(&metastr, str[i]);
			continue ;
		}
		if (is_str_equal(prev_metastr, "") || is_str_equal(prev_metastr, "|"))
		{
			ft_arr_append(arr, metastr);
			free(prev_metastr);
			if (!str[i])
			{
				*idx = --i;
				free(metastr);
				return (true);
			}
			prev_metastr = metastr;
			metastr = new_str((char []){str[i], '\0'});
		}
		else
		{
			printf(BRED "minishell: syntax error near unexpected token `%s'\n" END, metastr);
			free(prev_metastr);
			free(metastr);
			return (false);
		}
	}
	if (is_str_equal(prev_metastr, ""))
		ft_arr_append(arr, metastr);
	*idx = --i;
	free(metastr);
	free(prev_metastr);
	return (true);
}

t_res	metachar_scan(char **arr[], char **buf, char *str, int *idx)
{
	if (is_metachar(str[*idx]) && !is_quotes_open(*buf))
	{
		buf_to_arr(arr, buf);
		if (!is_metachar_valid(arr, str, idx))
			return (ERR);
		return (OK);
	}
	return (UNSET);
}
