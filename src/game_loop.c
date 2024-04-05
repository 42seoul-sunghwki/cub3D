/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/05 16:21:48 by minsepar         ###   ########.fr       */
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
	dda->camera_x = (2 * x_pixel_num / (double) WINWIDTH) - 1;
	printf("camera_x %f", dda->camera_x);
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
	printf("delta_dist_x: %f\n", dda->delta_dist_x);
	printf("delta_dist_y: %f\n", dda->delta_dist_y);
	dda->collision_flag = 0;
	init_side_dist(dda, user);
}

static void	perform_dda(t_dda *dda, t_user *user, t_map *map)
{
	printf("enter perform dda\n");
	while (dda->collision_flag == false)
	{
		printf("enter collision check @@@@@@@@\n");
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
	printf("side_dist_x [%f]", dda->side_dist_x);
	printf("side_dist_y [%f]", dda->side_dist_y);
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
}

/**
 * TODO: find a way to make realistic shade effect
*/
static void	draw_walls(t_dda *dda, t_mlx *mlx, t_user *user, t_map *map)
{
	int	line_height;
	int	color[] = {0, YELLOW, RED, GREEN, BLUE};

	line_height = (int)(WINHEIGHT / dda->perp_wall_dist);
	printf("perp wall dist [%f]\n", dda->perp_wall_dist);
	printf("line height [%d]\n", line_height);
	dda->draw_start_y = (-line_height / 2) + (WINHEIGHT / 2);
	if (dda->draw_start_y < 0)
		dda->draw_start_y = 0;
	dda->draw_end_y = line_height / 2 + (WINHEIGHT / 2);
	if (dda->draw_end_y >= WINHEIGHT)
		dda->draw_end_y = WINHEIGHT - 1;
	if (dda->side == 1)
		draw_vertical_line(mlx, dda, color[map->map[user->map_x][user->map_y] - '0'] / 2);
	else
		draw_vertical_line(mlx, dda, color[map->map[user->map_x][user->map_y] - '0']);
}

int	game_loop(void *arg)
{
	t_dda	dda;
	t_mlx	*graphic;
	t_user	*user;

	dda.cur_pixel_x = -1;
	graphic = arg;
	user = &graphic->user;
	while (++dda.cur_pixel_x < WINWIDTH)
	{
		init_data(&dda, user, dda.cur_pixel_x);
		perform_dda(&dda, user, &graphic->map);
		draw_walls(&dda, graphic, user, &graphic->map);
	}
	display_frame(graphic);
	return (0);
}
