/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:06:49 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/24 15:11:02 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	perform_dda(t_dda *dda, t_map *map)
{
	while (dda->collision_flag == false)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map->map[dda->map_y][dda->map_x] == '1')
			dda->collision_flag = true;
	}
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
}

static void	calculate_texture_helper(t_dda *dda, t_user *user)
{
	if (dda->side == 0)
	{
		dda->wall_pixel_x = user->y + dda->perp_wall_dist * dda->raydir_y;
		if (dda->raydir_x > 0)
			dda->texture_num = SOUTH;
		else
			dda->texture_num = NORTH;
	}
	else
	{
		dda->wall_pixel_x = user->x + dda->perp_wall_dist * dda->raydir_x;
		if (dda->raydir_y > 0)
			dda->texture_num = WEST;
		else
			dda->texture_num = EAST;
	}
}

static void	calculate_texture(t_mlx *graphic, t_dda *dda, t_user *user)
{
	t_pic	*texture;

	calculate_texture_helper(dda, user);
	texture = &graphic->block.pic[dda->texture_num];
	dda->wall_pixel_x -= floor(dda->wall_pixel_x);
	dda->texture_x = (int)(dda->wall_pixel_x * (float) texture->w);
	// printf("dda->texture_x: %d\n", dda->texture_x);
	if ((dda->side == 0 && dda->raydir_x > 0)
		|| (dda->side == 1 && dda->raydir_y < 0))
		dda->texture_x = texture->w - dda->texture_x - 1;
	dda->text_step = 1.0 * texture->h / dda->line_height;
	dda->text_pos = (dda->draw_start_y - ((WINHEIGHT) / 2 + WINWIDTH * user->zy
			+ user->z / dda->perp_wall_dist)
			+ dda->line_height / 2) * dda->text_step;
}

/**
 * TODO: find a way to make realistic shade effect
 * TODO: block comes out to be 540 x 480 fix it to make it square
*/
static void	draw_walls(t_dda *dda, t_mlx *graphic, t_user *user, t_map *map)
{
	// int		wall_index;
	float	half_line_height;

	(void) map;
	dda->line_height = (int)(WINHEIGHT * WALL_RATIO / dda->perp_wall_dist);
	half_line_height = dda->line_height / 2;
	dda->draw_start_y = -half_line_height + HALF_WINHEIGHT
		+ WINWIDTH * user->zy + user->z / dda->perp_wall_dist;
	if (dda->draw_start_y < 0)
		dda->draw_start_y = 0;
	dda->draw_end_y = half_line_height + HALF_WINHEIGHT + WINWIDTH * user->zy
		+ user->z / dda->perp_wall_dist;
	// if (dda->draw_end_y < 0)
	// {
	// 	printf("half_line_height: %f\n", half_line_height);
	// }
	if (dda->draw_end_y >= WINHEIGHT)
		dda->draw_end_y = WINHEIGHT - 1;
	// wall_index = map->map[dda->map_y][dda->map_x] - '0';
	calculate_texture(graphic, dda, user);
	draw_vertical_line(graphic, dda);
}

void	draw_wall_routine(void *arg)
{
	t_user	*user;
	t_mlx	*graphic;
	t_dda	*dda;

	dda = arg;
	graphic = dda->mlx;
	user = &graphic->user;
	while (dda->cur_pixel_x < dda->end_pixel_x)
	{
		init_data(dda, user, dda->cur_pixel_x);
		perform_dda(dda, &graphic->map);
		draw_walls(dda, graphic, user, &graphic->map);
		dda->cur_pixel_x++;
	}
	free(dda);
}

