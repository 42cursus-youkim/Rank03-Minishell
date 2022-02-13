#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef WIN32
#  include <sys/dirent.h>
# else
#  include <dirent.h>
# endif

# include <sys/stat.h>
# include <fcntl.h>

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include "minishell_type.h"

# include "ast_type.h"
# include "ast_node.h"

# include "lexer.h"
// # include "get_next_line.h"

#endif