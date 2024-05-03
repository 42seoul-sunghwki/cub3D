/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:06:49 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/03 22:37:04 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_open_door(int door_num)
{
	if (door_num == CHANGING_HDOOR
		|| door_num == CHANGING_VDOOR
		|| door_num == HDOOR_OPEN
		|| door_num == VDOOR_OPEN)
		return (true);
	return (false);
}

static void	dda_door(t_dda *dda, t_map *map)
{
	if (!(map->map[dda->map_y][dda->map_x] == 'V'
			|| map->map[dda->map_y][dda->map_x] == 'H'))
		return ;
	if (map->map[dda->map_y][dda->map_x] == 'V')
		dda->side_dist_x -= dda->delta_dist_x / 2;
	else
		dda->side_dist_y -= dda->delta_dist_y / 2;
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->side = 1;
	}
}

static void	check_ray_collision(t_dda *dda, t_map *map)
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
		if (map->map[dda->map_y][dda->map_x] == '1'
			|| (map->map[dda->map_y][dda->map_x] == 'V')
			|| (map->map[dda->map_y][dda->map_x] == 'H'))
			dda->collision_flag = true;
		if (is_open_door(map->map[dda->map_y][dda->map_x]))
			dda->changing_door = true;
	}
}

static void	perform_dda(t_mlx *graphic, t_dda *dda, t_map *map)
{
	dda->changing_door = false;
	check_ray_collision(dda, map);
	dda_door(dda, map);
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
	if (dda->cur_pixel_x == HALF_WINWIDTH)
		check_door_interaction(graphic, dda, map);
}

static bool	is_v_door(int map_texture)
{
	if ((map_texture == VDOOR_OPEN || map_texture == CHANGING_VDOOR)
		|| map_texture == VDOOR_CLOSED)
		return (true);
	return (false);
}

static bool	is_h_door(int map_texture)
{
	if (map_texture == HDOOR_OPEN || map_texture == CHANGING_HDOOR
		|| map_texture == HDOOR_CLOSED)
		return (true);
	return (false);
}

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
			dda->texture_num = WEST;
		else
			dda->texture_num = EAST;
	}
	else
	{
		dda->wall_pixel_x = user->x + dda->perp_wall_dist * dda->raydir_x;
		if (dda->raydir_y > 0)
			dda->texture_num = SOUTH;
		else
			dda->texture_num = NORTH;
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

void	check_interaction_opendoor(t_mlx *graphic, t_dda *dda, t_map *map)
{	
	if (dda->cur_pixel_x == HALF_WINWIDTH
		&& !(map->map[dda->map_y][dda->map_x] == VDOOR_CLOSED
		|| map->map[dda->map_y][dda->map_x] == HDOOR_CLOSED))
		check_door_interaction(graphic, dda, map);
}

void	draw_wall_routine(void *arg)
{
	t_user	*user;
	t_mlx	*graphic;
	t_dda	*dda;
	t_map	*map;

	dda = arg;
	graphic = dda->mlx;
	user = &graphic->user;
	map = &graphic->map;
	while (dda->cur_pixel_x < dda->end_pixel_x)
	{
		init_data(dda, user, dda->cur_pixel_x);
		perform_dda(graphic, dda, map);
		draw_walls(dda, graphic, user, map);
		if (dda->changing_door == true)
		{
			init_data(dda, user, dda->cur_pixel_x);
			perform_door_dda(dda, map);
			check_interaction_opendoor(graphic, dda, map);
			draw_walls(dda, graphic, user, map);
		}
		dda->cur_pixel_x++;
	}
	free(dda);
}
