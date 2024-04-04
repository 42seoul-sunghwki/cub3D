/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/05 00:03:15 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_side_dist(t_dda *dda, t_user *user)
{
	if (dda->raydir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (user->x - user->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (user->map_x + 1.0 - user->x) * dda->delta_dist_x;
	}
	if (dda->raydir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (user->y - user->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (user->map_y + 1.0 - user->y) * dda->delta_dist_y;
	}
}

static void	init_data(t_dda *dda, t_user *user, int x_pixel_num)
{
	dda->camera_x = (2 * x_pixel_num / (double) WIDTH) - 1;
	dda->raydir_x = user->dir_x + user->plane_x * dda->camera_x;
	dda->raydir_y = user->dir_y + user->plane_y * dda->camera_x;
	user->map_x = (int) user->x;
	user->map_y = (int) user->y;
	dda->delta_dist_x = sqrt(
			1 + (dda->raydir_y * dda->raydir_y)
			/ (dda->raydir_x * dda->raydir_x));
	dda->delta_dist_y = sqrt(
			1 + (dda->raydir_x * dda->raydir_x)
			/ (dda->raydir_y * dda->raydir_y));
	dda->collision_flag = 0;
	init_side_dist(dda, user);
}

static void	perform_dda(t_dda *dda, t_user *user, t_map *map)
{
	while (dda->collision_flag == false)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			user->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			user->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map->map[user->map_x][user->map_y]) 
			dda->collision_flag = true;
	}
}

int	game_loop(void *arg)
{
	int		x_pixel_num;
	t_dda	dda;
	t_mlx	*mlx;
	t_user	*user;

	x_pixel_num = -1;
	mlx = arg;
	user = &mlx->user;
	while (++x_pixel_num < WIDTH)
	{
		init_data(&dda, user, x_pixel_num);
		perform_dda(&dda, user, &mlx->map);
	}
}
