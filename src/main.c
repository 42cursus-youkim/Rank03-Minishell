#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc; (void)argv; (void)envp;

	// t_dict	*env = new_env(envp);
	// t_AST_NODE *word1 = new_ast_word("echo", NULL);
	// t_AST_NODE *word2 = new_ast_word("HELLO", NULL);
	// t_AST_NODE *word3 = new_ast_word("WORD", NULL);
	// // t_AST_NODE *redir = new_ast_redirect("a.txt", exp, REDIR_INPUT);
	// t_AST_COMMAND *cmd = new_ast_command(word1, NULL, (t_AST_NODE *[]){
	// 	word2, word3, NULL});
	// ast_command_repr(cmd, 0);
	// api_exec_cmd(cmd, env);
	// api_exec_cmd(NULL, NULL);
	api_exec_pipe(NULL, NULL);
	// del_dict(env);
	return (0);
}
