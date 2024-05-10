/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:06:49 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/11 00:06:38 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_dda_texture(t_mlx *graphic, t_map *map,
	t_dda *dda)
{
	t_door	*cur_door;

	cur_door = get_door(graphic, dda->map_y, dda->map_x);
	if (dda->side == 0)
	{
		if (is_v_door(map->map[dda->map_y][dda->map_x]))
			dda->texture = &graphic->sprite[DOOR_OPEN].img[cur_door->frame_num];
		else
			dda->texture = &graphic->block.pic[dda->texture_num];
	}
	else
	{
		if (is_h_door(map->map[dda->map_y][dda->map_x]))
			dda->texture = &graphic->sprite[DOOR_OPEN].img[cur_door->frame_num];
		else
			dda->texture = &graphic->block.pic[dda->texture_num];
	}
}

static void	calculate_texture_helper(t_dda *dda, t_user *user)
{
	if (dda->side == 0)
	{
		dda->wall_pixel_x = user->y + dda->perp_wall_dist * dda->raydir_y;
		if (dda->raydir_x > 0)
			dda->texture_num = EAST;
		else
			dda->texture_num = WEST;
	}
	else
	{
		dda->wall_pixel_x = user->x + dda->perp_wall_dist * dda->raydir_x;
		if (dda->raydir_y > 0)
			dda->texture_num = NORTH;
		else
			dda->texture_num = SOUTH;
	}
}

static void	calculate_texture(t_mlx *graphic, t_dda *dda, t_user *user)
{
	t_pic	*texture;

	calculate_texture_helper(dda, user);
	update_dda_texture(graphic, &graphic->map, dda);
	texture = dda->texture;
	dda->wall_pixel_x -= floor(dda->wall_pixel_x);
	dda->texture_x = (int)(dda->wall_pixel_x * (float) texture->w);
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
void	draw_walls(t_dda *dda, t_mlx *graphic, t_user *user, t_map *map)
{
	float	half_line_height;

	(void) map;
	dda->line_height = (int)(WINHEIGHT * WALL_RATIO / dda->perp_wall_dist);
	half_line_height = dda->line_height / 2;
	dda->draw_start_y = ((-half_line_height + HALF_WINHEIGHT)
			+ WINWIDTH * user->zy + user->z / dda->perp_wall_dist);
	if (dda->draw_start_y < 0)
		dda->draw_start_y = 0;
	dda->draw_end_y = half_line_height + HALF_WINHEIGHT + WINWIDTH * user->zy
		+ user->z / dda->perp_wall_dist;
	if (dda->draw_end_y >= WINHEIGHT)
		dda->draw_end_y = WINHEIGHT - 1;
	calculate_texture(graphic, dda, user);
	draw_vertical_line(graphic, dda);
}

