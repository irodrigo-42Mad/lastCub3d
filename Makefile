# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 11:31:25 by irodrigo          #+#    #+#              #
#    Updated: 2021/03/15 11:59:55 by irodrigo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# OS DISCLAIMER #
.DELETE_ON_ERROR:

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	LIBS := -lm -lbsd -lX11 -lXext
	MLX = mlx_linux/libmlx.a
	MINILIBX = mlx_linux
	INCLUDES = -I/usr/include -I. -Iincludes/ -I$(MINILIBX) -I$(LIBFT)
endif
ifeq ($(UNAME_S), Darwin)
	LIBS := -lz -framework OpenGL -framework AppKit
	MLX = mlx_ios/libmlx.dylib
	MINILIBX = mlx_ios
	INCLUDES = -I/usr/include -I. -Iincludes/ -I$(MINILIBX) -I$(LIBFT)
endif

# FILE NAME #
NAME = cub3D

# SOURCES #
SRC = 	ft_create_map ft_check_error ft_draw_game ft_elm_threatment ft_init_structs \
		ft_keyb_aux ft_keyboard ft_main ft_numbers ft_map_parser ft_parse_file ft_save_bmp \
		ft_screen_save ft_set_raycast ft_set_sprite ft_sprite_draw gnl ft_libft_aux \
		ft_file_check ft_aux_fnc ft_file_parser ft_clean ft_textures

SRCCUB = $(addsuffix .c, $(SRC))
OBJS = $(SRCCUB:.c=.o)

LIBFT = libft/libft.a

# COMPILER #
CC = gcc -Wall -Wextra -g  #-Werror# -g # -fsanitize=address

# COLOUR DEFINITION #
BLUE = \033[0;34m
GREEN = \033[1;32m
RESET = \033[0m

# CLEANING INSTRUCTION #
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS)
	@echo "$(BLUE)==========CREATING LIBFT==========$(RESET)"
	@cd libft && make re
	@echo "$(BLUE)==========CREATING MINILIBX==========$(RESET)"
	@make -C ${MINILIBX}
	@echo "$(BLUE)==========CREATING CUBE==========$(RESET)"
	@$(CC) $(INCLUDES) ${OBJS} $(LIBFT) $(MLX) ${LIBS} -o ${NAME}
	@echo "Done"
	@echo "$(BLUE)==========COPY LIBMLX.DYLIB==========$(RESET)"
	@cp ${MLX} ./
	@echo "Done"
	@echo "$(GREEN)==========WELLDONE==========$(RESET)"
	@echo "Success creating Cub3D file"

normi:
	@old_norminette $(SRCCUB) cub3d.h colors.h lst_errors.h ./libft/

clean:
	@$(RM) $(OBJS)
	@make -C $(MINILIBX)/ clean
	@make -C libft/ clean
	@$(RM) ${LIBFT}
	@${RM} libmlx.dylib
	@echo "$(GREEN)==========REMOVED==========$(RESET)"
	@echo "Success normal cleaning"

fclean: clean
	@$(RM) ${NAME}
	@$(RM) *.bmp
	@echo "$(GREEN)==========TOTALLY REMOVED==========$(RESET)"
	@echo "Success deepest cleaning"

re : fclean all

.PHONY: all clean fclean re shell addsuffix
