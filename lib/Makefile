# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:30:58 by youkim            #+#    #+#              #
#    Updated: 2022/03/02 16:51:27 by youkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Target & FLAGS =====
NAME     := libft.a

CC       := clang
CFLAGS   := -Wall -Wextra -Werror
AR       := ar -rcs
RM       := rm -f

PRE      := src
INC      := -I include

TEST     := test

# ===== Packages =====
PKGS     := ft_string dict system ft_math list error

ft_stringV  := new check util util2 array array2 split join
dictV    := new del util hash set get drop expand print status
systemV  := alloc read write gnl
ft_mathV := math compare check
listV    := list
errorV   := error

# ===== Macros =====
define choose_modules
	$(foreach pkg, $(1),\
		$(foreach file, $($(pkg)V),\
			$(PRE)/$(pkg)/$(file).c\
		)\
	)
endef

# ===== Sources & Objects & Include =====
SRC      := $(call choose_modules, $(PKGS))
OBJ      := $(SRC:%.c=%.o)

# ===== Rules =====
.PHONY: all re clean fclean

%.o: %.c
	@echo "  $(WU)$(<F)$(R) -> $(E)$(@F)"
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(NAME): $(OBJ)
	@$(AR) $@ $^
	@$(call log, V, 🗃️ archived with flag $(E)$(CFLAGS))

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(call log, G, 🗑 cleaned $(NAME)'s object files)

fclean: clean
	@$(RM) $(NAME)
	@$(call log, G, 🗑 cleaned $(NAME))

re: fclean all

# ===== Miscs =====

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
