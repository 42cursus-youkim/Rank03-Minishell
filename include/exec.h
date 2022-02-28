#ifndef EXEC_H
# define EXEC_H

typedef struct s_context
{
	t_fd	io_input;
	t_fd	io_output;
	char	*executable;
	char	**argv;
	char	**envp;
}	t_context;

//@func
/*
** < argv.c > */

char	**new_argv_from_cmd(char *executable, t_AST_COMMAND *cmd);
/*
** < context.c > */

void	context_init(t_context *context, t_AST_COMMAND *cmd, t_dict *env);
void	cmd_connect_redirects(t_AST_COMMAND *cmd);
void	del_context(t_context *context);
/*
** < exec.c > */

int		any_exec(t_AST_COMMAND *cmd, t_shell *shell);
void	child_proc(t_shell *shell, int index);
int		api_handle_exitcode(t_dict *env, int status);
int		api_exec_cmd_at(t_shell *shell, int index);
/*
** < util.c > */

bool	is_parent(pid_t pid);
bool	is_child(pid_t pid);
#endif