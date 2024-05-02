/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:39:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/03 00:52:40 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	interact_door(t_mlx *graphic, t_dda *dda, t_map *map)
{
	t_sprite_vec	*door_vec;
	t_sprite_node	*node;

	door_vec = &graphic->door_vec;
	node = get_sprite(door_vec,
			graphic->door_map[dda->map_y * map->w + dda->map_x]);
	if (node->status == 0)
		node->status = -1;
	node->status = -node->status;
	if (graphic->total_frame - node->start_frame
		< (size_t) graphic->sprite[DOOR_CLOSE].num_img * 2)
	{
		node->start_frame -= (size_t) graphic->sprite[DOOR_CLOSE].num_img * 2
			- (graphic->total_frame - node->start_frame);
	}
	else
		node->start_frame = graphic->total_frame;
}

void	check_door_interaction(t_mlx *graphic, t_dda *dda, t_map *map)
{
	t_user	*user;

	user = &graphic->user;
	if (dda->cur_pixel_x != HALF_WINWIDTH
		|| graphic->interact_frame != graphic->total_frame
		|| !(map->map[dda->map_y][dda->map_x] == VDOOR_CLOSED
		|| map->map[dda->map_y][dda->map_x] == HDOOR_CLOSED))
		return ;
	if (dda->perp_wall_dist < INTERACT_DISTANCE)
	{
		if (map->map[dda->map_y][dda->map_x] == VDOOR_CLOSED
			|| map->map[dda->map_y][dda->map_x] == VDOOR_OPEN)
		{
			map->map[dda->map_y][dda->map_x] = CHANGING_VDOOR;
			interact_door(graphic, dda, map);
		}
		else if (map->map[dda->map_y][dda->map_x] == HDOOR_CLOSED)
		{
			map->map[dda->map_y][dda->map_x] = CHANGING_HDOOR;
			interact_door(graphic, dda, map);
		}
	}
}
