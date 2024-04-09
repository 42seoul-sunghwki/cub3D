/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/09 21:22:02 by minsepar         ###   ########.fr       */
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
	dda->text_step = 1.0 * IMG_H / dda->line_height;
	dda->text_pos = (dda->draw_start_y - (WINHEIGHT) / 2
			+ dda->line_height / 2) * dda->text_step;
}

/**
 * TODO: find a way to make realistic shade effect
 * TODO: block comes out to be 540 x 480 fix it to make it square
*/
static void	draw_walls(t_dda *dda, t_mlx *graphic, t_user *user, t_map *map)
{
	int	wall_index;

	dda->line_height = (int)(WINHEIGHT * 1.34 / dda->perp_wall_dist);
	dda->draw_start_y = (-(dda->line_height) / 2) + (WINHEIGHT / 2);
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
	t_dda			*dda;
	t_mlx			*graphic;
	t_user			*user;
	size_t			cur_time;

	graphic = arg;
	dda = &graphic->dda;
	dda->cur_pixel_x = -1;
	user = &graphic->user;
	while (++dda->cur_pixel_x < WINWIDTH)
	{
		init_data(dda, user, dda->cur_pixel_x);
		perform_dda(dda, user, &graphic->map);
		draw_walls(dda, graphic, user, &graphic->map);
	}
	// sleep(1);
	// printf("line_height %d\n", dda.line_height);
	display_frame(graphic);
	cur_time = get_time_in_us();
	printf("fps: [%lu]\n", 1000000/(cur_time - graphic->time));
	graphic->time = cur_time;
	return (0);
}
