/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:24:57 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/05 13:25:37 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	perform_dda(t_mlx *graphic, t_dda *dda, t_map *map)
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
