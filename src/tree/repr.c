#include "minishell.h"

static char	*new_range_repr(int begin, int end)
{
	return (new_str_join_freed("", 5, (t_tempstr []){
			{"(", 0},
			{new_itoa(begin), 1},
			{"~", 0},
			{new_itoa(end), 1},
			{")", 0},
		}));
}

static void	ast_expansion_repr(t_AST_expansion **expansions, int indent)
{
	int		i;
	char	*str;

	if (!expansions)
		return ;
	i = -1;
	while (expansions[++i])
	{
		str = new_str_join_freed("", 5, (t_tempstr[]){
			{" -" HGRN, 0},
			{expansions[i]->parameter, 0},
			{END, 0},
			{new_range_repr(expansions[i]->begin, expansions[i]->end), 1},
			{"\n", 0},
			});
		printf("%*s%s", indent, "", str);
		free(str);
	}
}

static void	ast_word_repr(t_AST_NODE *node, int indent)
{
	printf(BWHT "%*s%s\n" END, indent, "", node->text);
	ast_expansion_repr(node->expansions, indent);
}

static void	ast_redirect_repr(t_AST_NODE *node, int indent)
{
	static char	*op_str[] = {
		"◀️ ", "◀️◀️", "▶️ ", "▶️▶️",
	};

	printf(BYEL "%*s%s%s\n" END, indent, "",
		op_str[node->op], node->text);
	ast_expansion_repr(node->expansions, indent);
}

void	ast_node_repr(t_AST_NODE *node, int level)
{
	const int	indent = level * 2;

	if (node->type == WORD)
		return (ast_word_repr(node, indent));
	else if (node->type == REDIRECT)
		ast_redirect_repr(node, indent);
}
