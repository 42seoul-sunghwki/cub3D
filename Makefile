NAME =	./bin/cub3D

CC	=	cc

FLAGS =  -g -Wall -Werror -Wextra

SRC_DIR =	src

OBJ_DIR =	build

SRC =	main.c mlx_color.c mlx_hooks.c mlx_pixel.c frame.c init_struct.c \
		game_loop.c init_dda_data.c handle_keypress.c handle_mouse.c \
		collision_check.c quick_sort_sprite.c

BONUS_SRC =	main_bonus.c mlx_color_bonus.c mlx_hooks_bonus.c mlx_pixel_bonus.c frame_bonus.c init_struct_bonus.c \
		game_loop_bonus.c init_dda_data_bonus.c handle_keypress_bonus.c handle_mouse_bonus.c \
		collision_check_bonus.c

SRCS =	$(addprefix src/, $(SRC))

OBJ =	$(addprefix build/, $(SRC))

OBJS =	$(OBJ:.c=.o)

BONUS_OBJS = $(BONUS_OBJ:.c=.o)

MLX_DIR = ./lib/mlx

MLX =	$(MLX_DIR)/bin/libmlx.dylib

LIBFT_DIR = ./lib/libftprintf

LIBFT = $(LIBFT_DIR)/bin/libftprintf.a

DEP = dependencies.d

BIN_DIR = bin

MLX_LINUX = mlx_Linux

all: $(NAME)

$(MLX):
	make -C ./lib/mlx all

$(OBJ_DIR):
	mkdir -p build

$(BIN_DIR):
	mkdir -p bin

#for linux

# $(MLX_LINUX): 
# 	make -C ./lib/mlx_linux all

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
# 	$(CC) $(FLAGS) -Iinclude -Imlx_linux -O3 -c $< -o $@

# $(NAME): $(OBJS) $(MLX_LINUX) $(LIBFT) | $(BIN_DIR)
# 	$(CC) $(OBJS) -L./lib/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz \
# 	$(LIBFT) -o $(NAME)

#for MAC

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -Iinclude -MMD -MF $(DEP) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) $(OBJS) -L./lib/mlx/bin -lmlx -framework OpenGL -framework AppKit \
	$(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all bonus

release: $(OBJS) $(LIBFT) $(MLX)
	$(CC) -O3 $(FLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit \
	$(LIBFT) -o $(NAME)

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