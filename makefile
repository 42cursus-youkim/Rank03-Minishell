# ===== Target & FLAGS =====
NAME     := minishell

CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
RM       := rm -rf

PRE      := src
LIB      := lib
INC      := -I include/ -I $(LIB)/include
LIBFT    := $(LIB)/libft.a

# ===== Test & Debugging =====
DFLAGS	 :=  -g #-DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
VFLAGS   := --leak-check=full --show-leak-kinds=all \
			--track-origins=yes
HGEN     := hgen

# ===== Packages =====
PKGS     :=


# ===== Macros =====
define choose_modules
	$(foreach pkg, $(1),\
		$(foreach file, $($(pkg)V),\
			$(PRE)/$(pkg)/$(file).c\
		)\
	) $(PRE)/main.c
endef

$(LIBFT):
	@make all -C $(LIB) DFLAGS="$(DFLAGS)"

# ===== Sources & Objects & Include =====
SRC     := $(call choose_modules, $(PKGS))
OBJ     := $(SRC:%.c=%.o)

# ===== Rules =====
%.o: %.c
	@echo "   $(WU)$(<F)$(R) -> $(E)$(@F)"
	@$(CC) $(CFLAGS) $(DFLAGS) $(INC) -c -o $@ $<

# @$(call build_library)
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) -o $@ $^
	@$(call log, V, 🚀 linked with flag $(R)$(DFLAGS)$(E)$(CFLAGS))

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(call log, G, 🗑 cleaned $(NAME)'s object files)

fclean: clean
	@$(RM) $(NAME)
	@$(call log, G, 🗑 cleaned $(NAME))

tclean: fclean
	@make fclean -C $(LIB)
# @$(call log, G, 🗑 Remove $(LIBFT))

re: fclean all

# ===== Custom Rules =====
red: fclean docs all cls
ald: docs all cls

docs:
	@set -e;\
		for p in $(PKGS); do\
			$(HGEN) -I include/$$p.h src/$$p;\
		done
	@$(call log, G, Updated Docs)

run: docs all
	@./$(NAME)
# test: docs all cls
# 	@$(call log, G, 🧪 Running Test)
# 	@./$(NAME)

leak: docs all cls
	@$(call log, Y, 🧪 Running Leak Test)
	@colour-valgrind $(VFLAGS) ./$(NAME)

supp: docs all cls
	@$(call log, Y, Creating Leak Suppressions,...)
	@valgrind $(VFLAGS) --gen-suppressions=all ./$(NAME)

.PHONY: all re clean fclean test red docs $(LIBFT)

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