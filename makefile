# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:30:44 by youkim            #+#    #+#              #
#    Updated: 2022/03/02 16:48:23 by youkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Target & FLAGS =====
NAME     := minishell

CC       := clang
CFLAGS   := -Wall -Wextra -Werror
RM       := rm -rf

PRE      := src
INC      := -I ~/.brew/opt/readline/include -I./include/ -I./lib/include
LIB		 := -L ~/.brew/opt/readline/lib -lreadline -L./lib -lft
LIBFT    := lib/libft.a

# ===== Test & Debugging =====
DFLAGS	 := #-g3 #-DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
VFLAGS   := --leak-check=full --show-leak-kinds=all \
			--track-fds=yes \
			--track-origins=yes
HGEN     := hgen

# ===== Packages =====
PKGS     := scanner lexer parser \
			api shell prompt tree errormsg \
			open exec pipe builtin

# AST
scannerV := scanner scanner_list expansion util util2 util3 \
			dollar_scan1 dollar_scan2 metachar_scan1 metachar_scan2
lexerV   := lexer tokenizer util
parserV  := parser new1 new2 del util1 util2 expander1 expander2 heredoc_parser

# Shell API
apiV     := signal path tilde util env1 env2
shellV   := shell script
promptV  := prompt interrupt ps check util
treeV    := repr1 repr2
errormsgV:= error

# Script
openV    := open redirect heredoc file check
execV    := context exec argv util
pipeV    := pipe send status util
builtinV := builtin cd echo exit env export unset pwd util check

# ===== Macros =====
define choose_modules
	$(foreach pkg, $(1),\
		$(foreach file, $($(pkg)V),\
			$(PRE)/$(pkg)/$(file).c\
		)\
	) $(PRE)/main.c
endef

# ===== Sources & Objects & Include =====
SRC      := $(call choose_modules, $(PKGS))
OBJ      := $(SRC:%.c=%.o)

# ===== Rules =====
.PHONY: all re clean fclean test red docs

%.o: %.c
	@printf "$(Y)%-10s$(WU)$(<F)$(R) -> $(E)$(@F)\n" [$(subst src/,,$(*D))]
	@$(CC) $(CFLAGS) $(DFLAGS) $(INC) -c -o $@ $<

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) $(LIB) $^ -o $@
	@$(call log, V, 🚀 linked with flag $(R)$(DFLAGS)$(E)$(CFLAGS))

$(LIBFT):
	@make --no-print-directory all -C lib/ DFLAGS="$(DFLAGS)"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(call log, G, 🗑 cleaned $(NAME)'s object files)

fclean: clean
	@$(RM) $(NAME)
	@$(call log, G, 🗑 cleaned $(NAME))

tclean: fclean
	@make fclean -C lib

# @$(call log, G, 🗑 Remove $(LIBFT))

re: fclean all

# ===== Custom Rules =====
red: tclean docs all cls
ald: docs all cls

docs:
	@make --no-print-directory docs -C lib/
	@set -e;\
		for p in $(PKGS); do\
			$(HGEN) -I include/$$p.h src/$$p 1> /dev/null;\
		done

run: docs all
	@./$(NAME)

leak: docs all cls
	@$(call log, Y, 🧪 Running Leak Test)
	@valgrind $(VFLAGS) ./$(NAME)

supp: docs all cls
	@$(call log, Y, Creating Leak Suppressions,...)
	@valgrind $(VFLAGS) \
		--log-file=supp3.txt\
		--gen-suppressions=all ./$(NAME)

# ===== Colors =====
cls:
	@set -e; clear

R  ?= \033[0;91m
WU ?= \033[4;37m
C  ?= \033[0;96m
CU ?= \033[4;36m
Y  ?= \033[0;33m
YU ?= \033[4;33m
G  ?= \033[0;92m
V  ?= \033[0;35m
E  ?= \033[0m
BD ?= \033[1m

define log
	printf "$($(strip $(1)))$(strip $(2))$(strip $(3))$(E)\n"
endef
