# ===== Target & FLAGS =====
NAME     := libft.a

CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -std=c99
DFLAGS	 := -g #-DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
VFLAGS   := --leak-check=full --show-leak-kinds=all \
			--track-origins=yes
AR       := ar -rcs
RM       := rm -f

PRE      := src
INC      := -I include

HGEN     := hgen
TEST     := test

# ===== Packages =====
PKGS     := string

stringV  := utils array split

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
%.o: %.c
	@echo "  $(WU)$(<F)$(R) -> $(E)$(@F)"
	@$(CC) $(CFLAGS) $(DFLAGS) $(INC) -c -o $@ $<

$(NAME): $(OBJ)
	@$(AR) $@ $^
	@$(call log, V, 🗃️ archived with flag $(R)$(DFLAGS)$(E)$(CFLAGS))

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(call log, G, 🗑 cleaned $(NAME)'s object files)

fclean: clean
	@$(RM) $(NAME)
	@$(call log, G, 🗑 cleaned $(NAME))

re: fclean all

# ===== Custom Rules =====
red: fclean docs all
ald: docs all

docs:
	@set -e;\
		for p in $(PKGS); do\
			$(HGEN) -I include/$$p.h src/$$p;\
		done
	@$(call log, V, 📝 Generating Docs)

testdry: docs all
	@$(call log, Y, Preparing Test,...)
	@$(CC) $(DFLAGS) $(INC) $(NAME) $(TEST).c -o test
	@$(call log, G, Compiled Test)

test: testdry cls
	@$(call log, G, 🧪 Running Test)
	@./$(TEST)

leak: docs all cls
	@$(call log, Y, 🧪 Running Leak Test)
	@$(CC) $(DFLAGS) $(INC) $(NAME) test.c -o test
	@colour-valgrind $(VFLAGS) ./test
	@rm test
#$(shell ruby -e "puts (1..11).to_a.shuffle.join  (' ')")
leaksup: docs all cls
	@echo "$(Y)<Creating Leak Suppressions>$(E)"
	@$(CC) $(DFLAGS) $(INC) $(NAME) tests/test.c -o test
	@valgrind $(VFLAGS) --gen-suppressions=yes ./test
	@rm test

.PHONY: all re clean fclean test red docs

# ===== Miscs =====
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