SHELL = bash

# VARIABLES
CC = gcc
CFLAG = -Wall -Wextra -Werror
RM = rm -rf

NAME = minishell

INCD_DIR = ./include

LIBFT_DIR = ./lib
LIBFT_NAME = ft
LIBFT = $(LIBFT_DIR)/lib$(LIBFT_NAME).a

SRCS_DIR = ./src
SRCS =	main.c
INDEX = 0

OBJS_DIR = ./obj
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

#STYLE
FG_TEXT = \033[38;5;85m
FG_DEBUG = \033[48;5;203m
CL_RESET = \033[0m
CL_BOLD = \033[1m
CL_BRESET = \033[21m

# RULE
.PHONY : all clean fclean re tclean rere $(LIBFT_NAME)_clean $(LIBFT_NAME)_fclean

all : $(LIBFT) $(NAME)

clean :
	@$(RM) $(OBJS_DIR)
	@echo -e "🗑 Remove $(CL_BOLD)$(NAME)'s OBJs$(CL_RESET) ... Done"

fclean : clean
	@$(RM) $(NAME)
	@echo -e "🗑 Remove $(CL_BOLD)$(NAME)$(CL_RESET) ... Done"

re : fclean all

tclean : $(LIBFT_NAME)_fclean fclean

rere : tclean all

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -I $(INCD_DIR) $(OBJS) -L $(LIBFT_DIR) -l$(LIBFT_NAME) -o $(NAME) -g
	@echo -e "  $(CL_RESET)$(FG_TEXT)Done$(CL_RESET)"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(eval INDEX = $(shell expr $(INDEX) + 1))
	@if [ $(INDEX) = 1 ] ; then \
		echo -en "$(FG_TEXT)Creating $(CL_BOLD)$(NAME) ◼︎︎︎︎︎︎︎︎◼︎◼︎︎︎︎︎︎︎︎◼︎◼︎︎︎︎︎︎︎︎◼︎" ; \
	else \
		echo -en "$(FG_TEXT)◼︎︎︎︎︎︎︎︎◼︎◼︎︎︎︎︎︎︎︎◼◼︎︎︎︎︎︎︎︎◼︎" ; \
	fi
	@$(CC) $(CFLAGS) -I $(INCD_DIR) -I $(LIBFT_DIR) -c $< -o $@ -g

# Lib
$(LIBFT) : 
	@make --no-print-directory -C $(LIBFT_DIR) all

$(LIBFT_NAME)_clean :
	@make --no-print-directory -C $(LIBFT_DIR) clean

$(LIBFT_NAME)_fclean :
	@make --no-print-directory -C $(LIBFT_DIR) fclean