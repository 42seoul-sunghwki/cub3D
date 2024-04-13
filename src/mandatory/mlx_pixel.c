/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:45:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/13 17:58:50 by minsepar         ###   ########.fr       */
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

/**
 * TODO: need to work on sky and floor, if done with color, add texture
*/
void	draw_texture_line(t_mlx *graphic, t_data *data, t_dda *dda, int y)
{
	int		tex_y;
	int		color;
	t_data	*pic;

	pic = &graphic->block.pic[dda->texture_num].data;
	tex_y = (int)dda->text_pos % IMG_H;
	if (tex_y < 0)
		tex_y *= -1;
	dda->text_pos += dda->text_step;
	color = my_mlx_pixel_get(pic, dda->texture_x, tex_y);
	my_mlx_pixel_put(data, dda->cur_pixel_x, y, color);
}

void	draw_vertical_line(t_mlx *graphic, t_dda *dda)
{
	t_data	*data;
	int		i;

	data = &graphic->img_data[graphic->num_frame];
	i = -1;
	while (++i < WINHEIGHT)
	{
		if (i < dda->draw_start_y)
			my_mlx_pixel_put(data, dda->cur_pixel_x, i, graphic->block.c_trgb);
		else if (i < dda->draw_end_y)
			draw_texture_line(graphic, data, dda, i);
		else if (i >= dda->draw_end_y)
			my_mlx_pixel_put(data, dda->cur_pixel_x, i, graphic->block.f_trgb);
	}
}
