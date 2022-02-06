# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojekim <hyojekim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/29 19:18:56 by hyojekim          #+#    #+#              #
#    Updated: 2021/07/29 19:18:58 by hyojekim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -f

NAME = libft.a

INCD = libft.h get_next_line.h

FIRST_FILE = ft_atoi.c

SRCS_1 = 	ft_atoi.c			\
			ft_isalnum.c		\
			ft_isalpha.c		\
			ft_isascii.c		\
			ft_isdigit.c		\
			ft_isprint.c		\
			ft_toupper.c		\
			ft_tolower.c		\
			ft_strlen.c			\
			ft_strlcpy.c		\
			ft_strlcat.c		\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_strnstr.c		\
			ft_strncmp.c		\
			ft_strdup.c			\
			ft_memset.c			\
			ft_bzero.c			\
			ft_memcpy.c			\
			ft_memccpy.c		\
			ft_memmove.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_calloc.c

SRCS_2 =	ft_itoa.c			\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_substr.c			\
			ft_strtrim.c		\
			ft_strjoin.c		\
			ft_strmapi.c		\
			ft_split.c

SRCS_3 =	get_next_line.c

SRCS = $(SRCS_1) $(SRCS_2) $(SRCS_3)

SRCS_BONUS = ft_lstnew.c		\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef BONUS_MODE
	OBJS_FILES = $(OBJS) $(OBJS_BONUS)
else
	OBJS_FILES = $(OBJS)
endif

#STYLE
FG_TEXT = \033[38;5;85m
CL_RESET = \033[0m
CL_BOLD = \033[1m
CL_BRESET = \033[21m


#RULE
.PHONY : all clean fclean re bonus

all : $(NAME)

clean :
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo -e "🗑 Remove $(CL_BOLD)$(NAME)'s OBJs$(CL_RESET) ... Done"

fclean : clean
	@$(RM) $(NAME)
	@echo -e "🗑 Remove $(CL_BOLD)$(NAME)$(CL_RESET) ... Done"

re : fclean all

$(NAME) : $(OBJS_FILES)
	@echo -e "  $(CL_RESET)$(FG_TEXT)Done$(CL_RESET)"
	@$(AR) $@ $^

bonus :
	@make BONUS_MODE=1 all

%.o : %.c
	@if [ "$(FIRST_FILE)" = "$<" ] ; then \
		echo -en "$(FG_TEXT)Creating $(CL_BOLD)$(NAME) ▉" ; \
	else \
		echo -en "▉" ; \
	fi
	@$(CC) $(CFLAGS) -c $< -o $@ -I ./


