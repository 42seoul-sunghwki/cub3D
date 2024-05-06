/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:39:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/05 20:11:17 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	interact_door(t_mlx *graphic, t_dda *dda)
{
	t_door	*door;

	door = get_door(graphic, dda->map_y, dda->map_x);
	door->direction = -door->direction;
	door->start_frame = graphic->total_frame;
}

void	check_door_interaction(t_mlx *graphic, t_dda *dda, t_map *map)
{
	t_user	*user;

	user = &graphic->user;
	if (graphic->interact_frame != graphic->total_frame
		|| dda->perp_wall_dist > INTERACT_DISTANCE)
		return ;
	if (map->map[dda->map_y][dda->map_x] == VDOOR_CLOSED
		|| map->map[dda->map_y][dda->map_x] == VDOOR_OPEN)
	{
		map->map[dda->map_y][dda->map_x] = CHANGING_VDOOR;
		interact_door(graphic, dda);
	}
	else if (map->map[dda->map_y][dda->map_x] == HDOOR_CLOSED
		|| map->map[dda->map_y][dda->map_x] == HDOOR_OPEN)
	{
		map->map[dda->map_y][dda->map_x] = CHANGING_HDOOR;
		interact_door(graphic, dda);
	}
}
