/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:24:59 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 17:16:34 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*print_format_c(t_print_dto *dto, ssize_t *return_len)
{
	char	*return_str;
	ssize_t	len;

	*return_len = 1;
	if (dto->nums[WIDTH] > *return_len)
		*return_len = dto->nums[WIDTH];
	return_str = (char *)ft_calloc(sizeof(char), *return_len + 1);
	if (!return_str)
		return (0);
	return_str[*return_len] = 0;
	len = 0;
	while (len < *return_len)
		return_str[len++] = ' ';
	if (dto->flag & MINUS_FLAG)
		return_str[0] = (char) va_arg(dto->ap, int);
	else
		return_str[*return_len - 1] = (char) va_arg(dto->ap, int);
	return (return_str);
}

static int	print_format_s_helper(t_print_dto *dto, ssize_t *return_len,
		char **return_str, ssize_t *len)
{
	if (dto->nums[PRECISION] != -1 && dto->nums[PRECISION] < *len)
		*len = dto->nums[PRECISION];
	dto->nums[PRINT_STR_LEN] = *len;
	*return_len = *len;
	if (dto->nums[WIDTH] > *len)
		*return_len = dto->nums[WIDTH];
	*return_str = (char *)ft_calloc(sizeof(char), *return_len + 1);
	if (!*return_str)
		return (-1);
	(*return_str)[*return_len] = 0;
	*len = 0;
	return (1);
}

char	*print_format_s(t_print_dto *dto, ssize_t *return_len)
{
	char	*return_str;
	char	*arg_str;
	ssize_t	len;

	*return_len = 1;
	if (dto->print_type == '%')
		arg_str = "%";
	else
		arg_str = va_arg(dto->ap, char *);
	if (!arg_str)
		arg_str = "(null)";
	len = ft_strlen(arg_str);
	if (print_format_s_helper(dto, return_len, &return_str, &len) == -1)
		return (0);
	while (len < *return_len)
		return_str[len++] = ' ';
	len = -1;
	if (dto->flag & MINUS_FLAG)
		while (len++ < dto->nums[PRINT_STR_LEN] - 1)
			return_str[len] = arg_str[len];
	else
		while (len++ < dto->nums[PRINT_STR_LEN] - 1)
			return_str[*return_len - dto->nums[PRINT_STR_LEN] + len]
				= arg_str[len];
	return (return_str);
}

char	*print_format_p(t_print_dto *dto, ssize_t *return_len)
{
	char			*return_str;
	ssize_t			len;
	ssize_t			temp_i;
	unsigned long	address;

	address = va_arg(dto->ap, unsigned long);
	numlen_p(dto, address, return_len, &len);
	return_str = (char *)malloc(*return_len + 1);
	temp_i = 0;
	if (!return_str)
		return (0);
	while (temp_i < *return_len)
		return_str[temp_i++] = ' ';
	if (dto->flag & MINUS_FLAG)
		temp_i = 0;
	else
		temp_i = *return_len - len;
	return_str[temp_i] = '0';
	return_str[temp_i + 1] = 'x';
	return_str[*return_len] = 0;
	if (dto->flag & MINUS_FLAG && dto->nums[PRECISION] != 0)
		recur_set_str_p(dto, return_str, len, address);
	else if (dto->nums[PRECISION] != 0)
		recur_set_str_p(dto, return_str, *return_len, address);
	return (return_str);
}
