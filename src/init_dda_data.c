/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dda_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:45:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/10 22:33:22 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_delta_dist(t_dda *dda)
{
	if (dda->raydir_x == 0)
		dda->delta_dist_x = INT_MAX;
	else
		dda->delta_dist_x = fabs(1 / dda->raydir_x);
	if (dda->raydir_y == 0)
		dda->delta_dist_y = INT_MAX;
	else
		dda->delta_dist_y = fabs(1 / dda->raydir_y);
}

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

void	init_data(t_dda *dda, t_user *user, int x_pixel_num)
{
	dda->camera_x = (2 * x_pixel_num / (float) WINWIDTH) - 1;
	dda->raydir_x = user->dir_x + user->plane_x * dda->camera_x;
	dda->raydir_y = user->dir_y + user->plane_y * dda->camera_x;
	user->map_x = (int) user->x;
	user->map_y = (int) user->y;
	init_delta_dist(dda);
	dda->collision_flag = false;
	init_side_dist(dda, user);
}
