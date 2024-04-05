/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/05 19:18:34 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (map->map[user->map_x][user->map_y] != '0')
			dda->collision_flag = true;
	}
	printf("side_dist_x [%f]\n", dda->side_dist_x);
	printf("delta_dist_x [%f]\n", dda->delta_dist_x);
	printf("side_dist_y [%f]\n", dda->side_dist_y);
	printf("delta_dist_y [%f]\n", dda->delta_dist_y);
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
	int	wall_index;

	(void) color;
	line_height = (int)(520 / dda->perp_wall_dist);
	printf("perp wall dist [%f]\n", dda->perp_wall_dist);
	printf("line height [%d]\n", line_height);
	dda->draw_start_y = (-line_height / 2) + (WINHEIGHT / 2);
	if (dda->draw_start_y < 0)
		dda->draw_start_y = 0;
	dda->draw_end_y = line_height / 2 + (WINHEIGHT / 2);
	if (dda->draw_end_y >= WINHEIGHT)
		dda->draw_end_y = WINHEIGHT - 1;
	wall_index = map->map[user->map_x][user->map_y] - '0';
	// printf("color: [%d]\n", );
	if (dda->side == 1)
		draw_vertical_line(mlx, dda, color[wall_index]);
	else
		draw_vertical_line(mlx, dda, color[wall_index]);
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
