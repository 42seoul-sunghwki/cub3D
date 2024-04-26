/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:51:37 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/22 22:37:46 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	dir_y_check_p(t_map *map, t_user *user)
{
	if (map->map[(int)(user->y + user->new_displacement_y + HITBOX)]
			[(int)(user->x - HITBOX)] == '0' &&
		map->map[(int)(user->y + user->new_displacement_y + HITBOX)]
			[(int)(user->x + HITBOX)] == '0')
		user->y += user->new_displacement_y;
}

void	dir_y_check_n(t_map *map, t_user *user)
{
	if (map->map[(int)(user->y + user->new_displacement_y - HITBOX)]
			[(int)(user->x - HITBOX)] == '0' &&
		map->map[(int)(user->y + user->new_displacement_y - HITBOX)]
			[(int)(user->x + HITBOX)] == '0')
		user->y += user->new_displacement_y;
}

void	dir_x_check_p(t_map *map, t_user *user)
{
	if (map->map[(int)(user->y - HITBOX)]
			[(int)(user->x + user->new_displacement_x + HITBOX)] == '0' &&
		map->map[(int)(user->y + HITBOX)]
			[(int)(user->x + user->new_displacement_x + HITBOX)] == '0')
		user->x += user->new_displacement_x;
}

void	dir_x_check_n(t_map *map, t_user *user)
{
	if (map->map[(int)(user->y - HITBOX)]
			[(int)(user->x + user->new_displacement_x - HITBOX)] == '0' &&
		map->map[(int)(user->y + HITBOX)]
			[(int)(user->x + user->new_displacement_x - HITBOX)] == '0')
		user->x += user->new_displacement_x;
}
