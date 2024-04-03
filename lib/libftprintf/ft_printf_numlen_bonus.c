/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numlen_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:35:23 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/03 20:31:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	numlen_d(t_print_dto *dto, long num, ssize_t *return_len)
{
	long	temp;

	*return_len = 0;
	temp = num;
	dto->len = 0;
	if (num < 0)
		num *= -1;
	if (num == 0 && dto->nums[PRECISION] == 0)
		dto->len = 0;
	else if (num == 0)
		dto->len = 1;
	while (num > 0)
	{
		dto->len++;
		num /= 10;
	}
	if (dto->nums[PRECISION] != -1 && dto->nums[PRECISION] > dto->len)
		dto->len = dto->nums[PRECISION];
	if (temp < 0 || (dto->flag & PLUS_FLAG) || (dto->flag & SPACE_FLAG))
		dto->len += 1;
	*return_len += dto->len;
	if (dto->nums[WIDTH] > *return_len)
		*return_len = dto->nums[WIDTH];
}

void	numlen_x(t_print_dto *dto, unsigned long num
		, ssize_t *return_len)
{
	unsigned long	temp;

	*return_len = 0;
	dto->len = 0;
	temp = num;
	if (num == 0 && dto->nums[PRECISION] == 0)
		dto->len = 0;
	else if (num == 0)
		dto->len = 1;
	while (num > 0)
	{
		dto->len++;
		num /= 16;
	}
	if (dto->nums[PRECISION] != -1 && dto->nums[PRECISION] > dto->len)
		dto->len = dto->nums[PRECISION];
	if (dto->flag & HASH_FLAG && temp != 0)
		dto->len += 2;
	*return_len += dto->len;
	if (dto->nums[WIDTH] > *return_len)
		*return_len = dto->nums[WIDTH];
}

void	numlen_p(t_print_dto *dto, unsigned long num, ssize_t *return_len,
		ssize_t *len)
{
	unsigned long	temp;

	*len = 2;
	*return_len = 0;
	temp = num;
	if (temp == 0 && dto->nums[PRECISION] != 0)
		*len = 3;
	while (temp > 0)
	{
		temp /= 16;
		*len += 1;
	}
	*return_len += *len;
	if (dto->nums[WIDTH] > *return_len)
		*return_len = dto->nums[WIDTH];
}

void	recur_set_str_p(t_print_dto *dto, char *return_str, ssize_t len,
		unsigned long num)
{
	char			*hex;

	hex = "0123456789abcdef";
	if (num > 15)
		recur_set_str(dto, return_str, len - 1, num / 16);
	return_str[len - 1] = hex[num % 16];
}

void	recur_set_str(t_print_dto *dto, char *return_str, ssize_t len, long num)
{
	char	*hex;

	if (dto->print_type == 'x' || dto->print_type == 'p')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (num > 15 && (dto->print_type == 'x' || dto->print_type == 'X'
			|| dto->print_type == 'p'))
		recur_set_str(dto, return_str, len - 1, num / 16);
	else if (num > 9 && !(dto->print_type == 'x' || dto->print_type == 'X'
			|| dto->print_type == 'p'))
		recur_set_str(dto, return_str, len - 1, num / 10);
	if (dto->print_type == 'x' || dto->print_type == 'X'
		|| dto->print_type == 'p')
		return_str[len - 1] = hex[num % 16];
	else
		return_str[len - 1] = num % 10 + '0';
}
