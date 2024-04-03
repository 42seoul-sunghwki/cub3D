/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_d_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:43:45 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/03 20:31:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_format_str_init(t_print_dto *dto, ssize_t *return_len
	, ssize_t *temp_i, char **return_str)
{
	*return_str = (char *)malloc(*return_len + 1);
	if (!(*return_str))
		return (-1);
	if ((dto->flag & DOT_FLAG) && dto->nums[PRECISION] == 0)
		dto->flag &= ~(ZERO_FLAG);
	*temp_i = 0;
	while (*temp_i < *return_len)
		(*return_str)[(*temp_i)++] = ' ';
	(*return_str)[*return_len] = 0;
	return (1);
}

void	print_format_set_temp_i(t_print_dto *dto, ssize_t *return_len
		, ssize_t *temp_i)
{
	if (!(dto->flag & MINUS_FLAG)
		&& (!(dto->flag & ZERO_FLAG) || dto->nums[PRECISION] > 0))
		*temp_i = *return_len - dto->len;
	else
		*temp_i = 0;
}

static void	print_format_d_prefix(t_print_dto *dto, long num
	, char **return_str, ssize_t *temp_i)
{
	if (num < 0)
		(*return_str)[(*temp_i)++] = '-';
	else if (dto->flag & PLUS_FLAG)
		(*return_str)[(*temp_i)++] = '+';
	else if (dto->flag & SPACE_FLAG)
		(*return_str)[(*temp_i)++] = ' ';
}

static void	print_format_d_zeros(t_print_dto *dto, ssize_t *return_len
	, char **return_str, ssize_t *temp_i)
{
	if ((dto->flag & ZERO_FLAG || dto->nums[PRECISION] > 0) && dto->len > 0)
	{
		if (dto->flag & MINUS_FLAG)
		{
			while (*temp_i < dto->len && dto->nums[PRECISION] != 0)
				(*return_str)[(*temp_i)++] = '0';
		}
		else
		{
			while (*temp_i < *return_len)
				(*return_str)[(*temp_i)++] = '0';
		}
	}
}

char	*print_format_d(t_print_dto *dto, ssize_t *return_len)
{
	char	*return_str;
	ssize_t	temp_i;
	long	num;

	if (dto->print_type == 'd' || dto->print_type == 'i')
		num = va_arg(dto->ap, int);
	else
		num = va_arg(dto->ap, unsigned int);
	numlen_d(dto, num, return_len);
	if (print_format_str_init(dto, return_len, &temp_i, &return_str) == -1)
		return (0);
	print_format_set_temp_i(dto, return_len, &temp_i);
	print_format_d_prefix(dto, num, &return_str, &temp_i);
	print_format_d_zeros(dto, return_len, &return_str, &temp_i);
	temp_i = num;
	if (temp_i < 0)
		temp_i *= -1;
	if (dto->flag & MINUS_FLAG && !(dto->nums[PRECISION] == 0 && num == 0))
		recur_set_str(dto, return_str, dto->len, temp_i);
	else if (dto->len > 0 && !(dto->nums[PRECISION] == 0 && num == 0))
		recur_set_str(dto, return_str, *return_len, temp_i);
	return (return_str);
}
