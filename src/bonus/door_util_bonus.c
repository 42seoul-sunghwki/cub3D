/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:22:05 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/12 23:08:19 by minsepar         ###   ########.fr       */
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

bool	is_close_door(int door_num)
{
	if (door_num == VDOOR_CLOSED
		|| door_num == HDOOR_CLOSED)
		return (true);
	return (false);
}

bool	is_v_door(int map_texture)
{
	if ((map_texture == VDOOR_OPEN || map_texture == CHANGING_VDOOR)
		|| map_texture == VDOOR_CLOSED)
		return (true);
	return (false);
}

bool	is_h_door(int map_texture)
{
	if (map_texture == HDOOR_OPEN || map_texture == CHANGING_HDOOR
		|| map_texture == HDOOR_CLOSED)
		return (true);
	return (false);
}

void	check_interaction_opendoor(t_mlx *graphic, t_dda *dda, t_map *map)
{
	t_user	*user;

	user = &graphic->user;
	if (dda->cur_pixel_x == HALF_WINWIDTH
		&& graphic->key_states[E_INTERACT]
		&& ((int)user->x != dda->map_x || (int)user->y != dda->map_y))
		check_door_interaction(graphic, dda, map);
}
