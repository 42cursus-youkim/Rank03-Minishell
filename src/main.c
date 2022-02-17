#include "minishell.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_dict	*env;

// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	t_AST_COMMAND cmd;


// 	env = new_env(envp);
// 	api_exec_cmd(&cmd, env);
// 	del_dict(env);
// 	return (0);
// }


int	main(void)
{
	t_AST_expansion	**exp = new_ast_expansions((t_AST_expansion *[]){
		new_ast_expansion("$HOME", 0, 5),
		new_ast_expansion("$USER", 10, 15),
		NULL,
	});

	t_AST_NODE *word = new_ast_word("HELLO", exp);
	t_AST_NODE *redir = new_ast_redirect("a.txt", exp, REDIR_INPUT);
	t_AST_COMMAND *cmd = new_ast_command(word, NULL, (t_AST_NODE *[]){
		word, word, redir, NULL});
	t_AST_PIPELINE *pip = new_ast_pipeline((t_AST_COMMAND *[]){
		cmd, cmd, cmd, NULL});

	ast_pipeline_repr(pip, 0);
	// ast_command_repr(cmd, 0);
	// ast_tree_print(cmd, COMMAND);
	// ast_node_repr(word, 1);
	// ast_node_repr(redir, 3);
	return (0);
}
