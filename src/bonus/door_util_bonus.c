/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:22:05 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/05 20:13:12 by minsepar         ###   ########.fr       */
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
	if (dda->cur_pixel_x == HALF_WINWIDTH)
		check_door_interaction(graphic, dda, map);
}
