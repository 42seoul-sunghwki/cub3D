/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:50:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/09 14:32:12 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MINUS_FLAG 1
# define PLUS_FLAG 2
# define SPACE_FLAG 4
# define ZERO_FLAG 8
# define HASH_FLAG 16
# define DOT_FLAG 32

# define WIDTH 0
# define PRECISION 1
# define PRINT_STR_LEN 2

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# include "libft/libft.h"
# include "libft/get_next_line_bonus.h"

typedef struct s_print_dto
{
	size_t		format_idx;
	size_t		print_idx;
	char		*print_str;
	char		print_type;
	size_t		size;
	char		flag;
	ssize_t		nums[3];
	va_list		ap;
	ssize_t		len;
}	t_print_dto;

/* ft_printf.c */
int			ft_printf(const char *format, ...);
void		parse_format(t_print_dto *dto, const char *format_str);
void		*append_str(t_print_dto *dto, const char *append_str, ssize_t len);

/* ft_printf_utils.c */
size_t		ft_strlen(const char *str);
t_print_dto	*dto_init(t_print_dto *dto);
void		dto_clear(t_print_dto *dto);
int			on_error(t_print_dto *dto, void *mem1);
void		set_flag_num(t_print_dto *dto, char c, int flag);

/* ft_printf_utils2.c */
int			is_type(int c);
int			is_flag(int c);
int			is_num(int num);
void		set_flag(t_print_dto *dto, char c);
char		*format_result(t_print_dto *dto, ssize_t *return_len);

/* ft_printf_numlen */
void		numlen_d(t_print_dto *dto, long num, ssize_t *return_len);
void		numlen_x(t_print_dto *dto, unsigned long num,
				ssize_t *return_len);
void		numlen_p(t_print_dto *dto, unsigned long num, ssize_t *return_len,
				ssize_t *len);
void		recur_set_str(t_print_dto *dto, char *return_str,
				ssize_t len, long num);
void		recur_set_str_p(t_print_dto *dto, char *return_str, ssize_t len,
				unsigned long num);

/* ft_printf_format.c */
char		*print_format_c(t_print_dto *dto, ssize_t *return_len);
char		*print_format_s(t_print_dto *dto, ssize_t *return_len);
char		*print_format_p(t_print_dto *dto, ssize_t *return_len);

/* ft_printf_format_d.c */
char		*print_format_d(t_print_dto *dto, ssize_t *return_len);
int			print_format_str_init(t_print_dto *dto, ssize_t *return_len,
				ssize_t *temp_i, char **return_str);
void		print_format_set_temp_i(t_print_dto *dto, ssize_t *return_len,
				ssize_t *temp_i);

/* ft_printf_format_x.c */
char		*print_format_x(t_print_dto *dto, ssize_t *return_len);
#endif
