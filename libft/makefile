# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 10:39:12 by irodrigo          #+#    #+#              #
#    Updated: 2020/01/13 10:47:02 by irodrigo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

CC=gcc

CFLAGS=-Wall -Werror -Wextra

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

HDDIRS=-I includes/

SRC=ft_strlen.c ft_isalpha.c ft_toupper.c ft_tolower.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_atoi.c ft_strrchr.c ft_memccpy.c ft_memmove.c ft_strncmp.c ft_strnstr.c ft_strlcat.c ft_strlcpy.c ft_calloc.c ft_strdup.c ft_strjoin.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_substr.c ft_strtrim.c ft_itoa.c ft_putendl_fd.c ft_split.c

SRCBONUS=ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ=$(SRC:.c=.o)

OBJBONUS=$(SRCBONUS:.c=.o)

$(NAME): ./libft.h
	@$(CC) $(CFLAGS) -c $(SRC) $(HDDIRS)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     libft.a     |"
	@echo "|   was created   |"
	@echo "[=================]"

bonus : ./libft.h
	@$(CC) $(CFLAGS) -c $(SRC) $(SRCBONUS) $(HDDIRS)
	ar rc $(NAME) $(OBJ) $(OBJBONUS)
	ranlib $(NAME)
	@echo $(SRCBONUS)

all: $(NAME)

clean:
	@$(RM) $(OBJ) $(OBJBONUS)
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     XXXXX.o     |"
	@echo "|  was destroyed  |"
	@echo "[=================]"

fclean: clean
	@$(RM) $(NAME) $(OBJBONUS)
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     libft.a     |"
	@echo "|   was removed   |"
	@echo "[=================]"

re: fclean all

.PHONY: clean fclean
