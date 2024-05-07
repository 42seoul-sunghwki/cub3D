/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:51:37 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/07 20:53:35 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dir_y_check_p(t_map *map, t_user *user, float new_displacement_y)
{
	if (map->map[(int)(user->y + new_displacement_y + HITBOX)]
		[(int)(user->x - HITBOX)] != '1' &&
	map->map[(int)(user->y + new_displacement_y + HITBOX)]
		[(int)(user->x + HITBOX)] != '1')
	user->y += new_displacement_y;
}

void	dir_y_check_n(t_map *map, t_user *user, float new_displacement_y)
{
	if (map->map[(int)(user->y + new_displacement_y - HITBOX)]
		[(int)(user->x - HITBOX)] != '1' &&
	map->map[(int)(user->y + new_displacement_y - HITBOX)]
		[(int)(user->x + HITBOX)] != '1')
	user->y += new_displacement_y;
}

void	dir_x_check_p(t_map *map, t_user *user, float new_displacement_x)
{
	if (map->map[(int)(user->y - HITBOX)]
		[(int)(user->x + new_displacement_x + HITBOX)] != '1' &&
	map->map[(int)(user->y + HITBOX)]
		[(int)(user->x + new_displacement_x + HITBOX)] != '1')
	user->x += new_displacement_x;
}

void	dir_x_check_n(t_map *map, t_user *user, float new_displacement_x)
{
	if (map->map[(int)(user->y - HITBOX)]
		[(int)(user->x + new_displacement_x - HITBOX)] != '1' &&
	map->map[(int)(user->y + HITBOX)]
		[(int)(user->x + new_displacement_x - HITBOX)] != '1')
	user->x += new_displacement_x;
}
