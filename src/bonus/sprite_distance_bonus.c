/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_distance_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:42:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/06 21:27:10 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float	get_distance_two_points(float x1, float y1, float x2, float y2)
{
	float	x_diff;
	float	y_diff;

	y_diff = y2 - y1;
	x_diff = x2 - x1;
	return (sqrt(x_diff * x_diff + y_diff * y_diff));
}

void	update_sprite_distance(t_mlx *graphic, t_user *user, t_sprite_vec *vec)
{
	int				i;
	t_sprite_node	*cur;

	(void) graphic;
	i = -1;
	while (++i < vec->size)
	{
		cur = get_sprite(vec, i);
		cur->distance
			= get_distance_two_points(user->x, user->y, cur->x, cur->y);
	}
}
