CC := clang
LIB := -L/usr/lib -lreadline
CFLAGS := -Wall -Wextra -Werror -std=c99
NAME := test

SRC := learnReadline.c
OBJ := $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(LIB) -o $@ $^

all: $(NAME)
run: all
	./$(NAME)
clean:
	$(RM) $(OBJ) $(NAME)