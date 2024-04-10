/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:15:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 16:08:04 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub_valid_door_bonus(t_map *map, int x, int y)
{
	if (map->map[y][x] == 'D')
	{
		if (!((map->map[y][x + 1] == '1' && map->map[y][x - 1] == '1')
			&& (map->map[y + 1][x] == '1' || map->map[y - 1][x] == '1')))
			return (FAIL);
	}
	return (SUCCESS);
}

static int	cub_valid_zero(t_map *map, int x, int y, int *flag)
{
	if (map->map[y][x] == '0')
	{
		if (map->map[y][x + 1] == ' ' || map->map[y][x - 1] == ' '
			|| map->map[y + 1][x] == ' ' || map->map[y - 1][x] == ' ')
			return (FAIL);
	}
	if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
		|| map->map[y][x] == 'W' || map->map[y][x] == 'E')
	{
		if (*flag == 1)
			return (FAIL);
		*flag = 1;
	}
	return (SUCCESS);
}

int	cub_map_valid(t_map *map)
{
	int	x;
	int	y;
	int	flag;

	y = -1;
	flag = 0;
	while (++y < map->h)
	{
		x = -1;
		while (++x < map->w)
		{
			if (cub_valid_zero(map, x, y, &flag) == FAIL)
				return (FAIL);
		}
	}
	return (SUCCESS);
}
