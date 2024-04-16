/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:51:37 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/16 13:10:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	dir_y_check_p(t_map *map, t_user *user, float new_displacement_y)
{
	// printf("yp\n");
	// printf("y: [%f] x: [%f]\n", user->y + new_displacement_y + HITBOX, user->x);
	if (map->map[(int)(user->y + new_displacement_y + HITBOX)]
			[(int)(user->x - HITBOX)] == '0' &&
		map->map[(int)(user->y + new_displacement_y + HITBOX)]
			[(int)(user->x + HITBOX)] == '0')
		user->y += new_displacement_y;
}

void	dir_y_check_n(t_map *map, t_user *user, float new_displacement_y)
{
	// printf("yn\n");
	// printf("y: [%f] x: [%f]\n", user->y + new_displacement_y + HITBOX, user->x);
	if (map->map[(int)(user->y + new_displacement_y - HITBOX)]
			[(int)(user->x - HITBOX)] == '0' &&
		map->map[(int)(user->y + new_displacement_y - HITBOX)]
			[(int)(user->x + HITBOX)] == '0')
		user->y += new_displacement_y;
}

void	dir_x_check_p(t_map *map, t_user *user, float new_displacement_x)
{
	// printf("xp\n");
	// printf("y: [%f] x: [%f]\n", user->y, user->x + new_displacement_x - HITBOX);
	if (map->map[(int)(user->y - HITBOX)]
			[(int)(user->x + new_displacement_x + HITBOX)] == '0' &&
		map->map[(int)(user->y + HITBOX)]
			[(int)(user->x + new_displacement_x + HITBOX)] == '0')
		user->x += new_displacement_x;
}

void	dir_x_check_n(t_map *map, t_user *user, float new_displacement_x)
{
	// printf("xn\n");
	// printf("y: [%f] x: [%f]\n", user->y, user->x + new_displacement_x - HITBOX);
	if (map->map[(int)(user->y - HITBOX)]
			[(int)(user->x + new_displacement_x - HITBOX)] == '0' &&
		map->map[(int)(user->y + HITBOX)]
			[(int)(user->x + new_displacement_x - HITBOX)] == '0')
		user->x += new_displacement_x;
}
