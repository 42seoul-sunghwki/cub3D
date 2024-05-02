/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_door_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:55:45 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/02 23:07:49 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	parse_map_door(t_mlx *graphic)
{
	t_map			*map;
	t_sprite_vec	*door_vec;
	int				i;
	int				j;
	int				num_door;

	map = &graphic->map;
	i = 0;
	num_door = 0;
	graphic->door_map = malloc(map->h * map->w);
	ft_memset(graphic->door_map, -1, map->h * map->w);
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (map->map[i][j] == VDOOR_CLOSED
				|| map->map[i][j] == HDOOR_CLOSED)
			{
				push_sprite(door_vec, create_sprite_node(i, j, DOOR_CLOSE, 0));
				graphic->door_map[i * map->w + j] = num_door++;
			}
		}
	}
}
