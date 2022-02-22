#ifndef PARSER_H
# define PARSER_H

typedef struct s_command_data
{
	int	name_index;
	int	num_prefix;
	int	num_suffix;
}	t_command_data;

//@func
/*
** < del.c > */

void			del_ast_expansions(t_AST_expansion *expansions[]);
void			del_ast_node(t_AST_NODE *node);
void			del_ast_command(t_AST_COMMAND *command);
void			del_ast_pipeline(t_AST_PIPELINE *pipeline);
/*
** < expander.c > */

t_res			expander(t_AST_PIPELINE *pipeline, t_dict *env);
/*
** < new1.c > */

t_AST_expansion	*new_ast_expansion(char *parameter, int begin, int end);
t_AST_expansion	**new_ast_expansions(t_AST_expansion *expansions[]);
t_AST_NODE		*new_ast_word( const char *text,
					t_AST_expansion *expansions[]);
t_AST_NODE		*new_ast_redirect( const char *text,
					t_AST_expansion *expansions[], t_redirect_op op);
/*
** < new2.c > */

t_AST_COMMAND	*new_ast_command(t_token tokens[], t_command_data data);
t_AST_PIPELINE	*new_ast_pipeline(t_AST_COMMAND *commands[],
					int commands_len);
/*
** < parser.c > */

t_AST_PIPELINE	*parser(t_token tokens[], t_dict *env);
/*
** < util1.c > */

t_redirect_op	redirection_option(char *str);
int				tokens_n_pipeline_count(int *size, t_token tokens[]);
int				commands_size(int pipe_count);
void			command_data_init( t_command_data *data, t_token tokens[],
					int begin, int end);
/*
** < util2.c > */

bool			is_ast_pipeline(t_AST_PIPELINE *pipeline);
bool			is_ast_command(t_AST_PIPELINE *pipeline);
#endif