/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_dda_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:33:44 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/12 23:02:48 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_door_frame(t_mlx *graphic, t_door *cur_door)
{
	t_sprite	*sprite;

	sprite = graphic->sprite;
	if (cur_door->direction == -1 && cur_door->frame_num != 0)
	{
		if ((graphic->total_frame - cur_door->start_frame)
			% sprite[DOOR_CLOSE].fpm == 0)
			cur_door->frame_num += cur_door->direction;
	}
	else if (cur_door->direction == 1 && cur_door->frame_num
		!= sprite[DOOR_CLOSE].num_img - 1)
	{
		if ((graphic->total_frame - cur_door->start_frame)
			% sprite[DOOR_CLOSE].fpm == 0)
			cur_door->frame_num += cur_door->direction;
	}
}

static void	update_map(t_mlx *graphic, t_door *cur_door)
{
	t_map	*map;
	int		y;
	int		x;

	map = &graphic->map;
	y = cur_door->index / map->w;
	x = cur_door->index - y * map->w;
	if (cur_door->direction == -1 && (map->map[y][x] == CHANGING_HDOOR
		|| map->map[y][x] == CHANGING_VDOOR) && cur_door->frame_num == 0)
	{
		if (map->map[y][x] == CHANGING_HDOOR)
			map->map[y][x] = HDOOR_OPEN;
		else if (map->map[y][x] == CHANGING_VDOOR)
			map->map[y][x] = VDOOR_OPEN;
	}
	else if (cur_door->direction == 1
		&& cur_door->frame_num == graphic->sprite[DOOR_OPEN].num_img - 1
		&& (map->map[y][x] == CHANGING_HDOOR
		|| map->map[y][x] == CHANGING_VDOOR))
	{
		if (map->map[y][x] == CHANGING_HDOOR)
			map->map[y][x] = HDOOR_CLOSED;
		else if (map->map[y][x] == CHANGING_VDOOR)
			map->map[y][x] = VDOOR_CLOSED;
	}
}

void	update_door(t_mlx *graphic)
{
	int			i;
	t_door		*cur_door;

	i = -1;
	while (++i < graphic->num_door)
	{
		cur_door = &graphic->door[i];
		update_door_frame(graphic, cur_door);
		update_map(graphic, cur_door);
	}
}

static void	dda_door_changing(t_dda *dda, t_map *map)
{
	if (is_v_door(map->map[dda->map_y][dda->map_x]))
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

void	perform_door_dda(t_dda *dda, t_map *map, t_door	*door)
{
	while (dda->collision_flag == false)
	{
		if (is_door_equal(dda->map_y, dda->map_x, door, dda->mlx))
		{
			dda->collision_flag = true;
			break ;
		}
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
	}
	dda_door_changing(dda, map);
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
}
