/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:56:52 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/03 20:31:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

t_print_dto	*dto_init(t_print_dto *dto)
{
	dto->flag = 0;
	dto->format_idx = 0;
	dto->print_idx = 0;
	dto->nums[WIDTH] = -1;
	dto->nums[PRECISION] = -1;
	dto->nums[PRINT_STR_LEN] = 0;
	dto->print_str = (char *)malloc(11);
	if (!dto->print_str)
		return (0);
	dto->size = 10;
	dto->len = 0;
	return (dto);
}

void	dto_clear(t_print_dto *dto)
{
	dto->flag ^= dto->flag;
	dto->nums[WIDTH] = -1;
	dto->nums[PRECISION] = -1;
	dto->nums[PRINT_STR_LEN] = 0;
}

int	on_error(t_print_dto *dto, void *mem1)
{
	free(dto->print_str);
	free(mem1);
	return (-1);
}

void	set_flag_num(t_print_dto *dto, char c, int flag)
{
	if (dto->nums[flag] == -1)
		dto->nums[flag] = 0;
	if (c != '.')
	{
		dto->nums[flag] *= 10;
		dto->nums[flag] += (c - '0');
	}
}
