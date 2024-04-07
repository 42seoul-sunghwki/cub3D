/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/07 18:53:43 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (map->map[user->map_x][user->map_y] != '0')
			dda->collision_flag = true;
	}
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
}

void	calculate_texture_helper(t_dda *dda, t_user *user)
{
	if (dda->side == 0)
	{
		dda->wall_pixel_x = user->y + dda->perp_wall_dist * dda->raydir_y;
		if (dda->raydir_y > 0)
			dda->texture_num = WEST;
		else
			dda->texture_num = EAST;
	}
	else
	{
		dda->wall_pixel_x = user->x + dda->perp_wall_dist * dda->raydir_x;
		if (dda->raydir_x > 0)
			dda->texture_num = SOUTH;
		else
			dda->texture_num = NORTH;
	}
}

void	calculate_texture(t_dda *dda, t_user *user)
{
	calculate_texture_helper(dda, user);
	dda->wall_pixel_x -= floor(dda->wall_pixel_x);
	dda->texture_x = (int)(dda->wall_pixel_x * (double) IMG_W);
	if ((dda->side == 0 && dda->raydir_x > 0)
		|| (dda->side == 1 && dda->raydir_y < 0))
		dda->texture_x = IMG_W - dda->texture_x - 1;
	dda->text_step = 1.0 * IMG_H / WINHEIGHT * 0.66;
	dda->text_pos = (dda->draw_start_y - (WINHEIGHT * 0.66) / 2
			+ dda->line_height / 2) * dda->text_step;
}

/**
 * TODO: find a way to make realistic shade effect
 * line_height is calculated by multiplying WINHEIGHT by 0.66 to make each
 * surface to be square and not a rectangle
*/
static void	draw_walls(t_dda *dda, t_mlx *graphic, t_user *user, t_map *map)
{
	int	wall_index;

	dda->line_height = (int)(WINHEIGHT * 0.66 / dda->perp_wall_dist);
	dda->draw_start_y = (-dda->line_height / 2) + (WINHEIGHT / 2);
	if (dda->draw_start_y < 0)
		dda->draw_start_y = 0;
	dda->draw_end_y = dda->line_height / 2 + (WINHEIGHT / 2);
	if (dda->draw_end_y >= WINHEIGHT)
		dda->draw_end_y = WINHEIGHT - 1;
	wall_index = map->map[user->map_x][user->map_y] - '0';
	calculate_texture(dda, user);
	if (dda->side == 1)
		draw_vertical_line(graphic, dda);
	else
		draw_vertical_line(graphic, dda);
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
