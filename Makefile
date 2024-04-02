# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 22:37:31 by sunghwki          #+#    #+#              #
#    Updated: 2024/04/02 22:40:12 by sunghwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

all : $(NAME)

$(NAME) : 
	make -C ./libft
	make -C ./mlx
	$(CC) $(CFLAGS) -o $(NAME) ./*.c ./libft/libft.a ./mlx/libmlx.a -framework OpenGL -framework AppKit
# tmp

clean :
	make clean -C ./libft
	make clean -C ./mlx

fclean : clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

