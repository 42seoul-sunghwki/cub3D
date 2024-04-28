/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:27:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/24 13:01:42 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_sanitize_enter(char *line)
{
	int		i;

	i = ft_strlen(line);
	if (line[i - 1] == '\n')
		line[i - 1] = '\0';
	return (SUCCESS);
}

void	ft_exit(char *str)
{
	printf("Error\n%s\n", str);
	exit (1);
}

void	get_img_addr(t_data *data)
{
	data->addr = mlx_get_data_addr(
			data->img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian
			);
}
