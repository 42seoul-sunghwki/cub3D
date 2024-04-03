NAME =	./bin/cub3D

CC	=	cc

FLAGS = -Wall -Wextra -Werror -g

SRC_DIR =	src

OBJ_DIR =	build

SRC =	main.c

SRCS =	$(addprefix src/, $(SRC))

OBJ =	$(addprefix build/, $(SRC))

OBJS =	$(OBJ:.c=.o)

MLX =	./lib/mlx/libmlx.dylib

all: $(NAME)

$(MLX):
	make -C ./lib/mlx all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft all bonus

clean:
	rm -rf $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: clean fclean all re