/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:45:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/03 21:57:49 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * put color data into corresponding img memory address 
 * 
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
		+ (y * data->line_length)
		+ (x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * returns: color data from corresponding img memory address
*/
int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	return (*(unsigned int *)(data->addr
		+ (y * data->line_length)
		+ (x * (data->bits_per_pixel / 8))));
}
