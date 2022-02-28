#include "minishell.h"

static t_res	heredoc_loop(t_list **scan_list, t_scan_data *data)
{
	t_res	scan_res;

	while (data->line[++(data->idx)])
	{
		scan_res = dollar_scan(scan_list, data);
		if (scan_res == OK)
			continue ;
		if (scan_res == ERR)
			return (ERR);
		ft_str_append(&data->buf, data->line[data->idx]);
	}
	buf_to_list(scan_list, &data->buf);
	free(data->buf);
	return (OK);
}

static t_res	list_tokenize_n_expand(char **line, t_list *list, t_dict *env)
{
	t_scan_node	*node;
	t_AST_NODE	*word;

	node = (t_scan_node *)list->content;
	word = new_ast_word(node->text, node->expansions);
	if (node_expansion(word, env, HEREDOC) == ERR)
		return (ERR);
	ft_str_replace(line, new_str(word->text));
	del_ast_node(word);
	del_list(&list, del_scan_node);
	return (OK);
}

t_res	replace_line_heredoc(char **line, t_dict *env)
{
	t_scan_data	data;
	t_list		*scan_list;

	scan_list = NULL;
	data.line = *line;
	data.idx = -1;
	data.type = HEREDOC;
	data.env = env;
	data.env_flag = false;
	data.buf = new_str("");
	if (heredoc_loop(&scan_list, &data) == ERR)
	{	
		del_list(&scan_list, del_scan_node);
		return (ERR);
	}
	if (list_tokenize_n_expand(line, scan_list, env) == ERR)
		return (ERR);
	return (OK);
}
