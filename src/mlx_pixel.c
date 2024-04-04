/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:45:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/04 16:08:40 by minsepar         ###   ########.fr       */
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

/**
 * returns resulting color from blending two foreground, background colors
*/
int	blend_trgb(int fg_color, int bg_color)
{
	float	alpha;
	int		return_trgb;

	return_trgb = 0;
	alpha = (0xFF - get_t(fg_color)) / 255.0;
	return_trgb = create_trgb(
			0,
			((1 - alpha) * (get_r(bg_color)) + alpha * (get_r(fg_color))),
			((1 - alpha) * (get_g(bg_color)) + alpha * (get_g(fg_color))),
			((1 - alpha) * (get_b(bg_color)) + alpha * (get_b(fg_color)))
			);
	return (return_trgb);
}
