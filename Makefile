# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 17:59:32 by minsepar          #+#    #+#              #
#    Updated: 2024/04/17 14:46:48 by minsepar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	./bin/mandatory/cub3D

NAME_BONUS = ./bin/bonus/cub3D

CC	=	cc

FLAGS =  -g -Wall -Werror -Wextra

SRC_MANDATORY_DIR :=	src/mandatory

SRC_BONUS_DIR :=	src/bonus

OBJ_MANDATORY_DIR :=	build/mandatory

OBJ_BONUS_DIR := build/bonus

SRC =	main.c mlx_color.c mlx_hooks.c mlx_pixel.c frame.c init_struct.c \
		cub_check.c cub_helper.c cub_list.c cub_map.c cub_read.c cub_slice.c \
		cub_map_valid.c cub_dup_valid.c cub_to_struct.c open_file.c \
		free_pointer.c ft_lib.c game_loop.c init_dda_data.c handle_keypress.c \
		collision_check.c collision_check_dir.c draw_floor.c

BONUS_SRC =	main_bonus.c mlx_color_bonus.c mlx_hooks_bonus.c mlx_pixel_bonus.c\
			frame_bonus.c init_struct_bonus.c cub_check_bonus.c \
			cub_helper_bonus.c cub_list_bonus.c cub_map_bonus.c \
			cub_read_bonus.c cub_slice_bonus.c cub_map_valid_bonus.c \
			cub_dup_valid_bonus.c cub_to_struct_bonus.c \
			open_file_bonus.c free_pointer_bonus.c ft_lib_bonus.c \
			game_loop_bonus.c init_dda_data_bonus.c handle_keypress_bonus.c \
			handle_mouse_bonus.c collision_check_bonus.c handle_arrow_bonus.c \
			mergesort_sprite_bonus.c sprite_list_bonus.c \
			update_sprite_bonus.c mouse_move_bonus.c

SRCS =	$(addprefix $(SRC_MANDATORY_DIR)/, $(SRC))

BONUS_SRCS = $(addprefix $(SRC_BONUS_DIR)/, $(BONUS_SRC))

MANDATORY_OBJ =	$(addprefix $(OBJ_MANDATORY_DIR)/, $(SRC))

MANDATORY_OBJS = $(MANDATORY_OBJ:.c=.o)

BONUS_OBJ = $(addprefix $(OBJ_BONUS_DIR)/, $(BONUS_SRC))

BONUS_OBJS = $(BONUS_OBJ:.c=.o)

MLX_DIR := ./lib/mlx

MLX =	$(MLX_DIR)/bin/libmlx.dylib

LIBFT_DIR := ./lib/libftprintf

LIBFT = $(LIBFT_DIR)/bin/libftprintf.a

DEP = dependencies.d

MANDATORY_BIN_DIR = bin/mandatory

BONUS_BIN_DIR = bin/bonus

MLX_LINUX = mlx_Linux

all: $(NAME)

$(MLX):
	make -C ./lib/mlx all

$(OBJ_DIR):
	mkdir -p $@

$(MANDATORY_BIN_DIR):
	mkdir -p $@

$(BONUS_BIN_DIR):
	mkdir -p $@

$(OBJ_BONUS_DIR):
	mkdir -p $@

#for linux

# $(MLX_LINUX): 
# 	make -C ./lib/mlx_linux all

# $(OBJ_MANDATORY_DIR)/%.o: $(SRC_MANDATORY_DIR)/%.c | $(OBJ_MANDATORY_DIR)
# 	$(CC) $(FLAGS) -Iinclude -Iinclude/mandatory -Imlx_linux -O3 -c $< -o $@

# $(NAME): $(MANDATORY_OBJS) $(MLX_LINUX) $(LIBFT) | $(MANDATORY_BIN_DIR)
# 	$(CC) $(OBJS) -L./lib/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz \
# 	$(LIBFT) -o $(NAME)
#	install_name_tool -change ./bin/libmlx.dylib ./lib/mlx/bin/libmlx.dylib $(NAME)

#bonus
# $(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
# 	$(CC) -pg -g -Iinclude -Iinclude/bonus -Imlx_linux -O3 -c $< -o $@

# $(NAME_BONUS): $(BONUS_OBJS) $(MLX_LINUX) $(LIBFT) | $(BONUS_BIN_DIR)
# 	$(CC) -pg -p $(BONUS_OBJS) -L./lib/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz \
# 	$(LIBFT) -o $(NAME_BONUS)
# install_name_tool -change ./bin/libmlx.dylib ./lib/mlx/bin/libmlx.dylib $(NAME_BONUS)

#for MAC
# mandatory
$(OBJ_MANDATORY_DIR)/%.o: $(SRC_MANDATORY_DIR)/%.c | $(OBJ_MANDATORY_DIR)
	$(CC) $(FLAGS) -Iinclude -Iinclude/mandatory -MMD -MF $(DEP) -c $< -o $@

$(NAME): $(MANDATORY_OBJS) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) $(MANDATORY_OBJS) -framework OpenGL -framework AppKit \
	$(LIBFT) $(MLX) -o  $(NAME)
	install_name_tool -change ./bin/libmlx.dylib ./lib/mlx/bin/libmlx.dylib $(NAME)

# bonus
$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(FLAGS) -Iinclude -Iinclude/bonus -MMD -MF $(DEP) -c $< -o $@

$(NAME_BONUS): $(BONUS_OBJS) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) $(BONUS_OBJS) -framework OpenGL -framework AppKit $(MLX) \
	$(LIBFT) -o $(NAME_BONUS)
	install_name_tool -change ./bin/libmlx.dylib ./lib/mlx/bin/libmlx.dylib $(NAME_BONUS)
	

$(LIBFT):
	make -C $(LIBFT_DIR) all bonus

clean:
	rm -rf $(MANDATORY_OBJS)
	rm -rf $(BONUS_OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	rm -rf $(DEP)
	make -C $(LIBFT_DIR) fclean

re: fclean all

reb: fclean bonus

run:
	@$(NAME) ./test.cub

runb:
	$(NAME_BONUS) ./test.cub

bonus: $(NAME_BONUS)

-include $(DEP)

.PHONY: clean fclean all re bonus run runb
