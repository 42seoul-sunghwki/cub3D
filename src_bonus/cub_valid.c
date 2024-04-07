/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:15:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/07 19:26:29 by sunghwki         ###   ########.fr       */
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

void	ft_d(int d[][2])
{
	d[0][0] = 1;
	d[0][1] = 0;
	d[1][0] = 0;
	d[1][1] = -1;
	d[2][0] = -1;
	d[2][1] = 0;
	d[3][0] = 0;
	d[3][1] = 1;
}

int	cub_valid(t_map *map)
{
	int	x;
	int	y;
	int	flag;
	int	d[4][2];

	y = -1;
	flag = 0;
	ft_d(d);
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
