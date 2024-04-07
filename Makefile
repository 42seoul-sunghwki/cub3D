NAME =	./bin/cub3D

CC	=	cc

FLAGS =  -g -Wall -Wextra -Werror

SRC_DIR =	src

OBJ_DIR =	build

SRC =	main.c mlx_color.c mlx_hooks.c mlx_pixel.c frame.c init_struct.c \
		game_loop.c init_dda_data.c handle_keypress.c

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

$(OBJ_DIR):
	mkdir -p build

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -Iinclude -MMD -MF $(DEP) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit \
	$(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all bonus

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(DEP)
	make -C $(LIBFT_DIR) fclean

re: fclean all

run:
	./$(NAME)

debug:
	lldb $(NAME)

-include $(DEP)

.PHONY: clean fclean all re