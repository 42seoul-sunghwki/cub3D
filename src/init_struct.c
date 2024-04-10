/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:53:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/09 22:10:05 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_block(t_block *block)
{
	int		i;

	i = -1;
	while (++i < 6)
	{
		init_pic(&(block->pic[i]));
	}
	block->f_trgb = UNDEFINED;
	block->c_trgb = UNDEFINED;
}

void	init_t_data(t_data *data)
{
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
}

void	init_pic(t_pic *pic)
{
	pic->w = IMG_W;
	pic->h = IMG_H;
	init_t_data(&(pic->data));
}

void	init_user(t_user *user, int x, int y, char pos)
{
	user->x = (double)x;
	user->y = (double)y;
	user->z = 48.0;
	user->map_x = 0;
	user->map_y = 0;
	user->dir_x = 0.0;
	user->dir_y = 0.0;
	if (pos == 'N')
		user->dir_y = 1.0;
	else if (pos == 'S')
		user->dir_y = -1.0;
	else if (pos == 'W')
		user->dir_x = -1.0;
	else if (pos == 'E')
		user->dir_x = 1.0;
	user->plane_x = 1.0;
	user->plane_y = -1.0;
	user->move_speed = 0.2;
	user->rot_speed = 0.2;
}
