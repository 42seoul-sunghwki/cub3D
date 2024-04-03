NAME = ./bin/libftprintf.a

SRCS = ft_printf.c ft_printf_utils.c ft_printf_utils2.c ft_printf_numlen.c \
ft_printf_format.c ft_printf_format_d.c ft_printf_format_x.c

BONUS_SRCS = $(SRCS:.c=_bonus.c)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = cc

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

all: $(OBJS)
	make -C ./libft bonus
	ar rucs $(NAME) $(OBJS)

$(LIBFT):
	make -C ./libft bonus

bonus: $(BONUS_OBJS)
	make -C ./libft all bonus
	ar rucs $(NAME) $(BONUS_OBJS)

re: 
	make -C ./libft re
	fclean all

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

.PHONY: bonus re all clean fclean
