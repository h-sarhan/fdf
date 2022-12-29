# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:01:09 by hsarhan           #+#    #+#              #
#    Updated: 2022/12/29 16:58:07 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MATH_SRC = matrix_operations.c matrix_transformations.c vector_arithmetic.c vector_operations.c
MATH_SRC := $(addprefix math/, $(MATH_SRC))

LINE_DRAWING_SRC = line_drawing.c
LINE_DRAWING_SRC := $(addprefix line_drawing/, $(LINE_DRAWING_SRC))

PARSING_SRC = parse_map.c parse_utils.c
PARSING_SRC := $(addprefix parsing/, $(PARSING_SRC))

SRC := $(MATH_SRC) $(PARSING_SRC) $(LINE_DRAWING_SRC) main.c key_input.c
SRC := $(addprefix src/, $(SRC))

OBJ_DIR = .obj
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPENDS := $(OBJ:.o=.d)
LIBFT = libft/libft.a

NAME = fdf
OS := $(shell uname)
CC = gcc
ifeq ($(OS),Linux)
	INC = -Iinclude -Ilibft  -I/usr/include -Imlx_linux
	OPTIMIZATION_FLAGS = -Ofast -march=native -flto -fno-signed-zeros -funroll-loops
	LINK_FLAGS = -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX = mlx_linux
else
	INC = -Iinclude -Ilibft -Imlx 
	OPTIMIZATION_FLAGS = -Ofast -march=native -flto -fno-signed-zeros -funroll-loops
	LINK_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit 
	MLX = mlx
endif


CFLAGS = -Wall -Wextra -march=native -g3 -pthread $(INC) \
			$(OPTIMIZATION_FLAGS) \
			-fsanitize=address
			

all:
	@make -j20 $(NAME)

$(OBJ_DIR)/%.o: %.c 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

$(LIBFT):
	make -C  libft

$(NAME): $(LIBFT) $(OBJ) Makefile
	-make -s  all -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LINK_FLAGS) -o $(NAME)

-include $(DEPENDS)

clean:
	-make -C $(MLX) clean
	-make -C libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

norm:
	-make -C libft norm
	norminette src include

re: fclean all

.PHONY: all re fclean clean
