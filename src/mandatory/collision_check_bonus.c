/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:21:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 14:21:22 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_walkable(int num_texture)
{
	if (num_texture == EMPTY
		|| num_texture == VDOOR_OPEN
		|| num_texture == HDOOR_OPEN
		|| num_texture == SPACE_MAP)
		return (true);
	return (false);
}

void	dir_y_check_p(t_map *map, t_user *user)
{
	if (is_walkable(map->map[(int)(user->y + user->new_displacement_y + HITBOX)]
		[(int)(user->x - HITBOX)])
			&& is_walkable(map->map[(int)
			(user->y + user->new_displacement_y + HITBOX)]
			[(int)(user->x + HITBOX)]))
		user->y += user->new_displacement_y;
}

void	dir_y_check_n(t_map *map, t_user *user)
{
	if (is_walkable(map->map[(int)(user->y + user->new_displacement_y - HITBOX)]
		[(int)(user->x - HITBOX)])
			&& is_walkable(map->map[(int)
			(user->y + user->new_displacement_y - HITBOX)]
			[(int)(user->x + HITBOX)]))
		user->y += user->new_displacement_y;
}

void	dir_x_check_p(t_map *map, t_user *user)
{
	if (is_walkable(map->map[(int)(user->y - HITBOX)]
		[(int)(user->x + user->new_displacement_x + HITBOX)])
			&& is_walkable(map->map[(int)(user->y + HITBOX)]
			[(int)(user->x + user->new_displacement_x + HITBOX)]))
		user->x += user->new_displacement_x;
}

void	dir_x_check_n(t_map *map, t_user *user)
{
	if (is_walkable(map->map[(int)(user->y - HITBOX)]
		[(int)(user->x + user->new_displacement_x - HITBOX)])
			&& is_walkable(map->map[(int)(user->y + HITBOX)]
			[(int)(user->x + user->new_displacement_x - HITBOX)]))
		user->x += user->new_displacement_x;
}
