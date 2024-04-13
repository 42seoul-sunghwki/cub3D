/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:48:40 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/13 17:48:51 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_floor_pixel(t_mlx *graphic, t_floor *floor, int i)
{
	int	j;
	int	color;

	j = -1;
	while (++j < WINWIDTH)
	{
		floor->cell_x = (int)(floor->floor_x);
		floor->cell_y = (int)(floor->floor_y);
		floor->tx = (int)(64 * (floor->floor_x - floor->cell_x)) & (63);
		floor->ty = (int)(64 * (floor->floor_y - floor->cell_y)) & (63);
		floor->floor_x += floor->floor_step_x;
		floor->floor_y += floor->floor_step_y;
		color = my_mlx_pixel_get(&graphic->block.pic[FLOOR].data,
				floor->tx, floor->ty);
		my_mlx_pixel_put(&graphic->img_data[graphic->num_frame],
			j, WINHEIGHT - 1 - i, color);
	}
}

void	draw_floor(t_mlx *graphic)
{
	t_floor			floor;
	t_user			*user;
	int				i;

	i = WINHEIGHT / 2;
	user = &graphic->user;
	while (--i > 0)
	{
		floor.raydir_x_start = user->dir_x - user->plane_x;
		floor.raydir_y_start = user->dir_y - user->plane_y;
		floor.raydir_x_end = user->dir_x + user->plane_x;
		floor.raydir_y_end = user->dir_y + user->plane_y;
		floor.p = i - HALF_WINHEIGHT;
		floor.pos_z = 1.34 * WINHEIGHT * 0.5;
		floor.row_distance = floor.pos_z / floor.p;
		floor.floor_step_x = -floor.row_distance
			* (floor.raydir_x_end - floor.raydir_x_start) / (WINWIDTH);
		floor.floor_step_y = -floor.row_distance
			* (floor.raydir_y_end - floor.raydir_y_start) / (WINWIDTH);
		floor.floor_x = user->x - floor.row_distance * floor.raydir_x_start;
		floor.floor_y = user->y - floor.row_distance * floor.raydir_y_start;
		draw_floor_pixel(graphic, &floor, i);
	}
}
