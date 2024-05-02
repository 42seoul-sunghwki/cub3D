/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_valid_helper_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:08:54 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/02 16:05:05 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	cub_valid_door_user(char **map, int x, int y, int *flag)
{
	static char	tmp[] = {'V', 'H'};
	int			i;

	i = -1;
	while (i < 2)
	{
		if (map[y][x] == tmp[i])
		{
			if (map[y - 1][x] == tmp[i] || map[y + 1][x] == tmp[i]
				|| map[y][x - 1] == tmp[i] || map[y][x + 1] == tmp[i])
				ft_exit("Invalid map\nDoor is too close to another door");
			if (i == 0 && map[y - 1][x] == '1' && map[y + 1][x] == '1'
				&& map[y][x - 1] != '1' && map[y][x + 1] != '1')
				return ;
			else if (i == 1 && map[y - 1][x] != '1' && map[y + 1][x] != '1'
				&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
				return ;
			else
				ft_exit("Invalid map\nDoor is not valid");
		}
		i++;
	}
	if (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		if (*flag == true)
			ft_exit("Invalid map\nUser is duplicated");
		*flag = true;
	}
}

static void	cub_valid_zombie(char **map, int x, int y)
{
	if (map[y][x] == 'Z')
	{
		if (map[y -1][x] == '1' && map[y + 1][x] == '1'
			&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
			ft_exit("Invalid map\nZombie is surrounded by wall");
	}
}

void	cub_valid_door_user_zombie(t_map *map)
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
			cub_valid_zombie(map->map, x, y);
		}
	}
	if (flag == false)
		ft_exit("Invalid map\nUser is not exist");
}
