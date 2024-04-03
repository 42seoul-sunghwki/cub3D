/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:30:43 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/03 20:31:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_type(int c)
{
	if (c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == '%')
		return (1);
	return (0);
}

int	is_flag(int c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#')
		return (1);
	return (0);
}

int	is_num(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	set_flag(t_print_dto *dto, char c)
{
	if (c == '-')
		dto->flag |= MINUS_FLAG;
	else if (c == '+')
		dto->flag |= PLUS_FLAG;
	else if (c == ' ')
		dto->flag |= SPACE_FLAG;
	else if (c == '0')
		dto->flag |= ZERO_FLAG;
	else if (c == '#')
		dto->flag |= HASH_FLAG;
	else if (c == '.')
	{
		dto->flag |= DOT_FLAG;
		set_flag_num(dto, '.', PRECISION);
	}
}

char	*format_result(t_print_dto *dto, ssize_t *return_len)
{
	if (dto->print_type == 'c')
		return (print_format_c(dto, return_len));
	else if (dto->print_type == 's')
		return (print_format_s(dto, return_len));
	else if (dto->print_type == 'p')
		return (print_format_p(dto, return_len));
	else if (dto->print_type == 'd')
		return (print_format_d(dto, return_len));
	else if (dto->print_type == 'i')
		return (print_format_d(dto, return_len));
	else if (dto->print_type == 'u')
		return (print_format_d(dto, return_len));
	else if (dto->print_type == 'x')
		return (print_format_x(dto, return_len));
	else if (dto->print_type == 'X')
		return (print_format_x(dto, return_len));
	else if (dto->print_type == '%')
		return (print_format_s(dto, return_len));
	return (0);
}
