/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:49:11 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/13 14:18:12 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	*append_str(t_print_dto *dto, const char *append_str, ssize_t len)
{
	ssize_t	temp_i;
	char	*temp_str;

	if (dto->print_idx + len > dto->size)
	{
		while (dto->print_idx + len > dto->size)
			dto->size *= 2;
		temp_str = (char *)ft_calloc(sizeof(char), dto->size + 1);
		if (!temp_str)
			return (0);
		temp_i = dto->print_idx;
		while (temp_i-- > 0)
			temp_str[temp_i] = dto->print_str[temp_i];
		free(dto->print_str);
		dto->print_str = temp_str;
	}
	temp_i = 0;
	while (temp_i < len)
	{
		dto->print_str[dto->print_idx] = append_str[temp_i];
		dto->print_idx++;
		temp_i++;
	}
	dto->print_str[dto->print_idx] = 0;
	return (dto->print_str);
}

static int	ft_printf_helper(t_print_dto *dto, const char *format_str,
		ssize_t *len, char *temp_str)
{
	parse_format(dto, format_str);
	temp_str = format_result(dto, len);
	if (!temp_str)
		return (on_error(dto, temp_str));
	if (!append_str(dto, temp_str, *len))
		return (on_error(dto, temp_str));
	free(temp_str);
	dto_clear(dto);
	return (1);
}

int	ft_printf(const char *format_str, ...)
{
	char		*temp_str;
	ssize_t		len;
	t_print_dto	dto;

	va_start(dto.ap, format_str);
	temp_str = 0;
	len = 0;
	if (!dto_init(&dto))
		return (-1);
	while (format_str[dto.format_idx])
	{
		if (format_str[dto.format_idx] == '%')
		{
			if (ft_printf_helper(&dto, format_str, &len, temp_str) == -1)
				return (-1);
		}
		else
			if (!append_str(&dto, &format_str[dto.format_idx], 1))
				return (on_error(&dto, 0));
		dto.format_idx++;
	}
	if (write(1, dto.print_str, dto.print_idx) == -1)
		dto.print_idx = -1;
	free(dto.print_str);
	return (dto.print_idx);
}

void	parse_format(t_print_dto *dto, const char *format_str)
{
	dto->format_idx++;
	while (is_flag(format_str[dto->format_idx]))
		set_flag(dto, format_str[dto->format_idx++]);
	while (is_num(format_str[dto->format_idx]))
		set_flag_num(dto, format_str[dto->format_idx++], WIDTH);
	if (format_str[dto->format_idx] == '.')
	{
		set_flag(dto, format_str[dto->format_idx++]);
		while (is_num(format_str[dto->format_idx]))
			set_flag_num(dto, format_str[dto->format_idx++], PRECISION);
	}
	dto->print_type = format_str[dto->format_idx];
}
