# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 17:59:32 by minsepar          #+#    #+#              #
#    Updated: 2024/05/12 16:15:22 by minsepar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	./bin/mandatory/cub3D

NAME_BONUS = ./bin/bonus/cub3D

CC	=	cc

FLAGS = -g -Wall -Werror -Wextra -O3

SRC_MANDATORY_DIR :=	src/mandatory

SRC_BONUS_DIR :=	src/bonus

OBJ_MANDATORY_DIR :=	build/mandatory

OBJ_BONUS_DIR := build/bonus

SRC =	main.c mlx_color.c mlx_hooks.c mlx_pixel.c frame.c init_struct.c \
		cub_check.c cub_helper.c cub_list.c cub_map.c cub_read.c cub_slice.c \
		cub_map_valid.c cub_dup_valid.c cub_to_struct.c open_file.c \
		free_pointer.c ft_lib.c game_loop.c init_dda_data.c handle_keypress.c \
		collision_check.c collision_check_dir.c calculate_keypress.c

BONUS_SRC =	main_bonus.c \
			mlx_color_bonus.c mlx_hooks_bonus.c mlx_pixel_bonus.c\
			frame_bonus.c init_struct_bonus.c cub_check_bonus.c \
			cub_helper_bonus.c cub_list_bonus.c cub_map_bonus.c \
			cub_slice_sprite_bonus.c cub_slice_sprite_helper_bonus.c cub_read_sprite_bonus.c cub_read_bonus.c cub_slice_bonus.c \
			cub_map_alloc_bonus.c cub_map_valid_bonus.c \
			cub_map_valid_helper_bonus.c cub_dup_valid_bonus.c \
			cub_dup_valid_helper_bonus.c cub_to_struct_bonus.c \
			astar_bonus.c astar_helper_bonus.c astar_thread_bonus.c \
			p_queue_bonus.c p_queue_helper_bonus.c queue_bonus.c \
			open_file_bonus.c free_pointer_bonus.c ft_lib_bonus.c \
			game_loop_bonus.c init_dda_data_bonus.c handle_keypress_bonus.c \
			handle_mouse_bonus.c collision_check_bonus.c handle_arrow_bonus.c \
			mergesort_sprite_bonus.c sprite_list_bonus.c \
			update_sprite_bonus.c mouse_move_bonus.c task_queue_bonus.c \
			thread_pool_bonus.c wall_thread_bonus.c draw_walls_bonus.c \
			draw_minimap_bonus.c draw_rotate_minimap_bonus.c draw_minimap_helper_bonus.c minimap_thread_bonus.c \
			draw_floor_thread_bonus.c \
			sprite_thread_bonus.c handle_keyrelease_bonus.c \
			handle_keys_bonus.c handle_jump_bonus.c sprite_distance_bonus.c \
			sound_bonus.c draw_user_bonus.c init_bonus.c \
			parse_door_map_bonus.c door_interaction_bonus.c door_map_bonus.c \
			door_dda_bonus.c calculate_sprite_bonus.c draw_user_util_bonus.c \
			door_util_bonus.c perform_dda_bonus.c init_mlx_bonus.c \
			draw_wall_routine_bonus.c door_draw_bonus.c

SRCS =	$(addprefix $(SRC_MANDATORY_DIR)/, $(SRC))

BONUS_SRCS = $(addprefix $(SRC_BONUS_DIR)/, $(BONUS_SRC))

MANDATORY_OBJ =	$(addprefix $(OBJ_MANDATORY_DIR)/, $(SRC))

MANDATORY_OBJS = $(MANDATORY_OBJ:.c=.o)

BONUS_OBJ = $(addprefix $(OBJ_BONUS_DIR)/, $(BONUS_SRC))

BONUS_OBJS = $(BONUS_OBJ:.c=.o)

MLX_DIR := ./lib/mlx

MLX =	$(MLX_DIR)/bin/libmlx.dylib

CWD = pwd

LIBFT_DIR := ./lib/libftprintf

LIBFT = $(LIBFT_DIR)/bin/libftprintf.a

DEP = dependencies.d

MANDATORY_BIN_DIR = bin/mandatory

BONUS_BIN_DIR = bin/bonus

MLX_LINUX = mlx_Linux

MLX_BIN = lib/mlx/bin

BUILD = build

BASS = lib/bass24-osx/intel/libbass.dylib

all: $(NAME)

$(MLX):
	make -C ./lib/mlx all

$(BUILD):
	mkdir -p $@

$(MLX_BIN):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(MANDATORY_BIN_DIR):
	mkdir -p $@

$(BONUS_BIN_DIR):
	mkdir -p $@

$(OBJ_BONUS_DIR):
	mkdir -p $@

$(OBJ_MANDATORY_DIR):
	mkdir -p $@

$(BASS):
	make -C lib/bass24-osx intel

# mandatory
$(OBJ_MANDATORY_DIR)/%.o: $(SRC_MANDATORY_DIR)/%.c | $(OBJ_MANDATORY_DIR)
	$(CC) $(FLAGS) -Ilib/libftprintf -Iinclude/mandatory -Ilib/mlx -MMD -MF $(DEP) -c $< -o $@

$(NAME): $(PWD) $(MANDATORY_OBJS) $(LIBFT) $(MLX) | $(MLX_BIN)
	@mkdir -p ./bin
	@mkdir -p ./bin/mandatory
	$(CC) $(FLAGS) $(MANDATORY_OBJS) -framework OpenGL -framework AppKit \
	$(LIBFT) $(MLX) -o  $(NAME)
	install_name_tool -change ./bin/libmlx.dylib ./lib/mlx/bin/libmlx.dylib $(NAME)

# bonus
$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(FLAGS) -Ilib/libftprintf -Iinclude/bonus -Ilib/mlx -Ilib/bass24-osx -MMD -MF $(DEP) -c $< -o $@

$(NAME_BONUS): $(PWD) $(BONUS_OBJS) $(LIBFT) $(MLX) $(BASS) | $(MLX_BIN)
	@mkdir -p ./bin
	@mkdir -p ./bin/bonus
	$(CC) $(FLAGS) $(BONUS_OBJS) -framework OpenGL -framework AppKit $(MLX) \
	$(LIBFT) -Wl,-rpath,$(PWD)/lib/bass24-osx/intel -Llib/bass24-osx/intel -lbass -o $(NAME_BONUS)
	install_name_tool -change ./bin/libmlx.dylib $(PWD)/lib/mlx/bin/libmlx.dylib $(NAME_BONUS)
	
$(LIBFT):
	make -C $(LIBFT_DIR) all bonus

clean:
	rm -rf $(MANDATORY_OBJS)
	rm -rf $(BONUS_OBJS)
	rm -rf $(DEP)
	rm -rf $(BASS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	make -C $(LIBFT_DIR) fclean

re: fclean all

reb: fclean bonus

run:
	@$(NAME) ./test_man.cub

runb:
	@$(NAME_BONUS) ./test_bonus.cub

bonus: $(NAME_BONUS)

-include $(DEP)

.PHONY: clean fclean all re bonus run runb
