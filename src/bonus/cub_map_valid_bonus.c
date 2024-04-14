/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_valid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:15:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/14 13:52:13 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub_valid_right_side(t_map *map, int x, int y)
{
	if (map->map[y][x] == '1')
		return (SUCCESS);
	else if (!(map->map[y][x] == ' '
		|| map->map[y][x] == 0 || map->map[y][x] == 1))
		ft_exit("Invalid map\nIt isn't surround by 1");
	if (x - 1 >= 0)
		cub_valid_right_side(map, x - 1, y);
	if (map->map[y][x] != 1)
	{
		map->map[y][x] = 1;
		if (y - 1 >= 0)
			cub_valid_right_side(map, x, y - 1);
		if (y + 1 < map->h)
			cub_valid_right_side(map, x, y + 1);
	}
	return (SUCCESS);
}

static int	cub_valid_left_side(t_map *map, int x, int y)
{
	if (map->map[y][x] == '1')
		return (SUCCESS);
	else if (!(map->map[y][x] == ' '
		|| map->map[y][x] == 0 || map->map[y][x] == 1))
		ft_exit("Invalid map\nIt isn't surround by 1");
	if (x + 1 < map->w)
		cub_valid_left_side(map, x + 1, y);
	if (map->map[y][x] != 0)
	{
		map->map[y][x] = 0;
		if (y + 1 < map->h)
			cub_valid_left_side(map, x, y + 1);
		if (y - 1 >= 0)
			cub_valid_left_side(map, x, y - 1);
	}
	return (SUCCESS);
}

static void	cub_valid_door_user(t_map *map)
{
	int	x;
	int	y;
	int	flag;

	y = -1;
	flag = false;
	while (++y < map->h)
	{
		x = -1;
		while (++x < map->w)
		{
			if (map->map[y][x] == 'D')
			{
				if (y - 1 < 0 || y + 1 > map->h
					|| x - 1 < 0 || x + 1 > map->w)
					ft_exit("Invalid map\nDoor is too close to the wall");
				if (map->map[y - 1][x] == 'D' || map->map[y + 1][x] == 'D'
					|| map->map[y][x - 1] == 'D' || map->map[y][x + 1] == 'D')
					ft_exit("Invalid map\nDoor is too close to another door");
				if (map->map[y - 1][x] == '1' && map->map[y + 1][x] == '1'
					&& map->map[y][x - 1] != '1' && map->map[y][x + 1] != '1')
					continue ;
				else if (map->map[y - 1][x] != '1' && map->map[y + 1][x] != '1'
					&& map->map[y][x - 1] == '1' && map->map[y][x + 1] == '1')
					continue ;
				else
					ft_exit("Invalid map\nDoor is not valid");
			}
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'W' || map->map[y][x] == 'E')
			{
				if (flag == true)
					ft_exit("Invalid map\nUser is duplicated");
				flag = true;
			}
		}
	}
}

int	cub_map_valid(t_map *map)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->w)
	{
		cub_valid_left_side(map, x, 0);
		cub_valid_right_side(map, x, 0);
		cub_valid_left_side(map, x, map->h - 1);
		cub_valid_right_side(map, x, map->h - 1);
	}
	y = 0;
	while (++y < map->h)
	{
		cub_valid_left_side(map, 0, y);
		cub_valid_right_side(map, map->w - 1, y);
	}
	cub_valid_door_user(map);
	return (SUCCESS);
}
