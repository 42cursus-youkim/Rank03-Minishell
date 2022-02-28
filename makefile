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
DFLAGS	 := -g3 #-DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
VFLAGS   := --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --suppressions=./supp_mac.txt \
			--suppressions=./supp.txt
HGEN     := hgen

# ===== Packages =====
PKGS     := prompt scanner lexer parser exec api builtin tree errormsg

scannerV := scanner scanner_list expansion util util2 util3 \
			dollar_scan1 dollar_scan2 metachar_scan1 metachar_scan2
lexerV   := lexer tokenizer util
parserV  := parser new1 new2 del util1 util2 expander1 expander2 heredoc_parser
promptV  := prompt interrupt ps util
apiV     := shell redirect signal path file util env1 env2
execV    := context exec pipe argv util
builtinV := builtin cd echo env export unset pwd util checks
treeV    := repr1 repr2
errormsgV:= error

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
		--log-file=supp2.txt\
		--gen-suppressions=all ./$(NAME)

.PHONY: $(NAME) all re clean fclean test red docs $(LIBFT)

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
