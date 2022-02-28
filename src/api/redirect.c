#include "minishell.h"

/*	get input for heredoc
	returns opened fd that points to it
*/
static t_fd	shell_heredoc(t_shell *shell, const char *eof)
{
	char	*line;
	t_fd	pipefd[PIPE_SIZE];

	if (pipe(pipefd) == ERR)
		return (ERR);
	while (true)
	{
		line = readline(shell->prompt.ps2);
		if (!line)
		{
			cursor_up();
			ft_write(1, shell->prompt.ps2);
			break ;
		}
		else if (is_str_equal(line, eof))
			break ;
		else
		{
			if (replace_line_heredoc(&line, shell->env) == ERR)
				break ;
			ft_writes(pipefd[PIPE_WRITE], (char *[]){line, "\n", NULL});
			free(line);
		}
	}
	if (line)
		free(line);
	close(pipefd[PIPE_WRITE]);
	return (pipefd[PIPE_READ]);
}

/*	currently:
	REDIR_INPUT = 0,
	REDIR_HEREDOC = 1,
	REDIR_OUTPUT = 2,
	REDIR_OUTPUT_APPEND = 3,
	NOT_REDIR = -1,
*/
t_res	api_open(t_fd *fd_p, t_AST_NODE *redirect, t_shell *shell)
{
	const char	*file = redirect->text;
	int			flag;
	const int	flags[5] = {
		O_RDONLY,
		OK,
		O_CREAT | O_WRONLY | O_TRUNC,
		O_CREAT | O_WRONLY | O_APPEND,
		ERR};

	flag = flags[redirect->op];
	if (flag == ERR)
		return (ERR);
	if (*fd_p > STDERR_FILENO)
		close(*fd_p);
	if (redirect->op == REDIR_HEREDOC)
		*fd_p = shell_heredoc(shell, file);
	else
		*fd_p = open(file, flag, 0644);
	if (*fd_p == ERR)
		return (ERR);
	return (OK);
}

void	cmd_try_open_redirect(
	t_AST_NODE *node, t_AST_COMMAND *cmd, t_shell *shell)
{
	t_fd	*fd_p;

	if (node->type != REDIRECT)
		return ;
	if (node->op == REDIR_HEREDOC || node->op == REDIR_INPUT)
		fd_p = &cmd->io[INPUT];
	else if (node->op == REDIR_OUTPUT || node->op == REDIR_OUTPUT_APPEND)
		fd_p = &cmd->io[OUTPUT];
	else
		return ;
	api_open(fd_p, node, shell);
}

/*	Opens fd, save to cmd and create file if needed
	does NOT connect fd to STDIN/STDOUT,
	that's done on command execution
*/
void	cmd_open_redirects(t_AST_COMMAND *cmd, t_shell *shell)
{
	int			i;
	const int	prefix_len = ast_nodes_len(cmd->prefixes);
	const int	suffix_len = ast_nodes_len(cmd->suffixes);

	i = -1;
	while (++i < prefix_len)
		cmd_try_open_redirect(
			cmd->prefixes[i], cmd, shell);
	i = -1;
	while (++i < suffix_len)
		cmd_try_open_redirect(
			cmd->suffixes[i], cmd, shell);
}

void	shell_open_redirects(t_shell *shell)
{
	int			i;
	const int	len = shell->script->commands_len;

	i = -1;
	while (++i < len)
		cmd_open_redirects(
			shell->script->commands[i], shell);
}
