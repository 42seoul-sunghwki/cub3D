/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:41:39 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/11 00:43:49 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_door_equal(int map_y, int map_x, t_door *door, t_mlx *graphic)
{
	if (map_y * graphic->map.w + map_x == door->index)
		return (true);
	return (false);
}