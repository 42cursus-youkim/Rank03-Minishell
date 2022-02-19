#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc; (void)argv; (void)envp;

	pid_t	pid;

	pid = fork();

	if (is_child(pid))
	{
		printf("Child process\n");
		char *argv[] = {"/bin/ls", "-l", NULL};
		char *envp[] = {NULL};
		if (execve(argv[0], argv, envp) == -1)
			printf("execve failed\n");
	}
	else if (is_parent(pid))
	{
		printf("Parent process\n");
		int status;
		waitpid(pid, &status, WNOHANG);
		printf ("Child process exited with status %d\n", api_handle_status(status));
  	}

	// t_dict	*env = new_env(envp);
	// t_AST_NODE *word1 = new_ast_word("echo", NULL);
	// t_AST_NODE *word2 = new_ast_word("HELLO", NULL);
	// t_AST_NODE *word3 = new_ast_word("WORD", NULL);
	// // t_AST_NODE *redir = new_ast_redirect("a.txt", exp, REDIR_INPUT);
	// t_AST_COMMAND *cmd = new_ast_command(word1, NULL, (t_AST_NODE *[]){
	// 	word2, word3, NULL});
	// ast_command_repr(cmd, 0);
	// api_exec_cmd(cmd, env);
	// del_dict(env);
	return (0);
}
