# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:01:09 by hsarhan           #+#    #+#              #
#    Updated: 2023/06/21 10:30:50 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MATH_SRC = matrix_operations.c matrix_transformations.c vector_arithmetic.c vector_operations.c projections.c
MATH_SRC += matrix_inverse.c matrix_inverse2.c
MATH_SRC := $(addprefix math/, $(MATH_SRC))

LINE_DRAWING_SRC = drawing.c clipping.c
LINE_DRAWING_SRC := $(addprefix line_drawing/, $(LINE_DRAWING_SRC))

PARSING_SRC = parse_map.c parse_utils.c
PARSING_SRC := $(addprefix parsing/, $(PARSING_SRC))

SRC := $(MATH_SRC) $(PARSING_SRC) $(LINE_DRAWING_SRC) main.c key_input.c
SRC := $(addprefix src/, $(SRC))

OBJ_DIR = .obj
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPENDS := $(OBJ:.o=.d)
LIBFT = lib/libft/libft.a

NAME = fdf
OS := $(shell uname)
CC = clang
ifeq ($(OS),Linux)
	INC = -Iinclude -I/usr/include -Ilib/mlx_linux
	OPTIMIZATION_FLAGS = -Ofast -march=native -fno-signed-zeros -funroll-loops
	LINK_FLAGS = -Llib/mlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX = lib/mlx_linux
else
	INC = -Iinclude -lib/Imlx
	OPTIMIZATION_FLAGS = -Ofast -march=native -fno-signed-zeros -funroll-loops
	LINK_FLAGS = -Llib/mlx -lmlx -framework OpenGL -framework AppKit
	MLX = lib/mlx
endif


CFLAGS = -Wall -Wextra -Werror -g3 -fno-omit-frame-pointer -fsanitize=address -pthread $(INC) \
			# $(OPTIMIZATION_FLAGS) \

all:
	# @make -j20 $(NAME)
	@make  $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -MJ $@.json $(CFLAGS) -MMD -MP -c -o $@ $<

$(LIBFT):
	make -C  lib/libft

$(NAME): $(LIBFT) $(OBJ) Makefile
	-make -s  all -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LINK_FLAGS) -o $(NAME)

-include $(DEPENDS)

db:
	@sed -e '1s/^/[\'$$'\n''/' -e '$$s/,$$/\'$$'\n'']/' $(OBJ_DIR)/src/**/*.o.json $(OBJ_DIR)/src/*.o.json > compile_commands.json

clean:
	-make -C $(MLX) clean
	-make -C lib/libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

norm:
	-make -C lib/libft norm
	norminette src include

re: fclean all

.PHONY: all re fclean clean
