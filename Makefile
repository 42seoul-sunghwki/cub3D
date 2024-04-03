NAME =	./bin/cub3D

CC	=	cc

FLAGS = -Wall -Wextra -Werror -g

SRC_DIR =	src

OBJ_DIR =	build

SRC =	main.c

SRCS =	$(addprefix src/, $(SRC))

OBJ =	$(addprefix build/, $(SRC))

OBJS =	$(OBJ:.c=.o)

MLX_DIR = ./lib/mlx

MLX =	$(MLX_DIR)/bin/libmlx.dylib

LIBFT_DIR = ./lib/libftprintf

LIBFT = $(LIBFT_DIR)/bin/libftprintf.a

DEP = dependencies.d

all: $(NAME)

$(MLX):
	make -C ./lib/mlx all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -Iinclude -MD -MF $(DEP) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all bonus

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEP)

.PHONY: clean fclean all re