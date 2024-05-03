/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_door_map_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:02:06 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/03 16:44:07 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	malloc_door_arr(t_mlx *graphic)
{
	t_map	*map;
	int		i;
	int		j;
	int		door_num;

	map = &graphic->map;
	i = -1;
	door_num = 0;
	while (++i < map->h)
	{
		j = -1;
		while (++j < map->w)
		{
			if (map->map[i][j] == VDOOR_CLOSED
				|| map->map[i][j] == HDOOR_CLOSED)
				door_num++;
		}
	}
	graphic->door = malloc(sizeof(t_door) * door_num);
	graphic->num_door = door_num;
}

static void	init_t_door(t_mlx *graphic, t_door *door, int y, int x)
{
	t_map	*map;

	map = &graphic->map;
	door->index = y * map->w + x;
	door->direction = 1;
	door->frame_num = graphic->sprite[DOOR_CLOSE].num_img - 1;
}

void	parse_door_map(t_mlx *graphic)
{
	t_map	*map;
	int		i;
	int		j;
	int		door_num;

	map = &graphic->map;
	i = -1;
	door_num = 0;
	malloc_door_arr(graphic);
	while (++i < map->h)
	{
		j = -1;
		while (++j < map->w)
		{
			if (map->map[i][j] == VDOOR_CLOSED
				|| map->map[i][j] == HDOOR_CLOSED)
			{
				init_t_door(graphic, &graphic->door[door_num], i, j);
				door_num++;
			}
		}
	}
}
