/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_x_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:40:33 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/03 20:31:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	print_format_x_zeros(t_print_dto *dto, ssize_t *return_len
	, char **return_str, ssize_t *temp_i)
{
	if (dto->flag & ZERO_FLAG || dto->nums[PRECISION] != 0)
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

static void	print_format_x_prefix(t_print_dto *dto, long num
	, char **return_str, ssize_t *temp_i)
{
	if (dto->flag & HASH_FLAG && num != 0)
		(*return_str)[(*temp_i)++] = '0';
	if (dto->flag & HASH_FLAG && num != 0 && dto->print_type == 'x')
		(*return_str)[(*temp_i)++] = 'x';
	else if (dto->flag & HASH_FLAG && num != 0)
		(*return_str)[(*temp_i)++] = 'X';
}

char	*print_format_x(t_print_dto *dto, ssize_t *return_len)
{
	char			*return_str;
	ssize_t			temp_i;
	unsigned long	num;

	num = va_arg(dto->ap, unsigned int);
	numlen_x(dto, num, return_len);
	if (print_format_str_init(dto, return_len, &temp_i, &return_str) == -1)
		return (0);
	print_format_set_temp_i(dto, return_len, &temp_i);
	print_format_x_prefix(dto, num, &return_str, &temp_i);
	print_format_x_zeros(dto, return_len, &return_str, &temp_i);
	if (dto->flag & MINUS_FLAG && !(dto->nums[PRECISION] == 0 && num == 0))
		recur_set_str(dto, return_str, dto->len, num);
	else if (dto->len > 0 && !(dto->nums[PRECISION] == 0 && num == 0))
		recur_set_str(dto, return_str, *return_len, num);
	return (return_str);
}
