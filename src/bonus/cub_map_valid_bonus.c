/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_valid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:15:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/14 14:23:02 by sunghwki         ###   ########.fr       */
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

static void	cub_valid_door_user(char **map, int x, int y, int *flag)
{
	if (map[y][x] == 'D')
	{
		if (map[y - 1][x] == 'D' || map[y + 1][x] == 'D'
			|| map[y][x - 1] == 'D' || map[y][x + 1] == 'D')
			ft_exit("Invalid map\nDoor is too close to another door");
		if (map[y - 1][x] == '1' && map[y + 1][x] == '1'
			&& map[y][x - 1] != '1' && map[y][x + 1] != '1')
			return ;
		else if (map[y - 1][x] != '1' && map[y + 1][x] != '1'
			&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
			return ;
		else
			ft_exit("Invalid map\nDoor is not valid");
	}
	if (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		if (*flag == true)
			ft_exit("Invalid map\nUser is duplicated");
		*flag = true;
	}
}

static void	cub_valid_door_user_zombie(t_map *map)
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
			if (y - 1 < 0 || y + 1 > map->h
				|| x - 1 < 0 || x + 1 > map->w)
				continue ;
			cub_valid_door_user(map->map, x, y, &flag);
			if (map->map[y][x] == 'Z')
			{
				if (map->map[y -1][x] == '1' && map->map[y + 1][x] == '1'
						&& map->map[y][x - 1] == '1'
						&& map->map[y][x + 1] == '1')
					ft_exit("Invalid map\nZombie is surrounded by wall");
			}
		}
	}
	if (flag == false)
		ft_exit("Invalid map\nUser is not exist");
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
	cub_valid_door_user_zombie(map);
	return (SUCCESS);
}
