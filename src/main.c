#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc; (void)argv; (void)envp;

	char *str = "abcde";
	printf("0:2 slice is %s\n", new_str_slice(str, 0, 2));
	// t_dict	*env = new_env(envp);
	// t_AST_NODE *word1 = new_ast_word("echo", NULL);
	// t_AST_NODE *word2 = new_ast_word("HELLO", NULL);
	// t_AST_NODE *word3 = new_ast_word("WORD", NULL);
	// // t_AST_NODE *redir = new_ast_redirect("a.txt", exp, REDIR_INPUT);
	// t_AST_COMMAND *cmd = new_ast_command(word1, NULL, (t_AST_NODE *[]){
	// 	word2, word3, NULL});
	// ast_command_repr(cmd, 0);
	// api_run_cmd(cmd, env);
	// del_dict(env);
	return (0);
}
