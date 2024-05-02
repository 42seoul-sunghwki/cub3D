/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_door_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:55:45 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/03 00:55:02 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	parse_map_init(t_mlx *graphic, int *i, int *num_door)
{
	*i = -1;
	*num_door = 0;
	graphic->door_map = malloc(graphic->map.h * graphic->map.w);
	ft_memset(graphic->door_map, -1, graphic->map.h * graphic->map.w);
}

void	parse_map_door(t_mlx *graphic)
{
	t_map			*map;
	int				i;
	int				j;
	int				num_door;
	t_sprite_node	*node;

	map = &graphic->map;
	parse_map_init(graphic, &i, &num_door);
	while (++i < map->h)
	{
		j = -1;
		while (++j < map->w)
		{
			if (map->map[i][j] == VDOOR_CLOSED
				|| map->map[i][j] == HDOOR_CLOSED)
			{
				node = create_sprite_node(j + 0.5, i + 0.5, DOOR_CLOSE, 0);
				node->status = 2;
				push_sprite(&graphic->door_vec, node);
				push_sprite(&graphic->sprite_vec, node);
				graphic->door_map[i * map->w + j] = num_door++;
			}
		}
	}
}
