/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:15:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/09 19:37:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub_valid_right_side(t_map *map, int x, int y)
{
	int	ret;

	ret = SUCCESS;
	if (map->map[y][x] == '1')
	{
		return (SUCCESS);
	}
	else if (map->map[y][x] != ' ')
	{
		perror("Error\nInvalid map");
		return (FAIL);
	}
	if (x - 1 >= 0 && map->map[y][x - 1])
	{
		ret = cub_valid_right_side(map, x - 1, y);
		if (ret == FAIL)
			return (FAIL);
	}
	if (y + 1 < map->h && map->map[y + 1][x])
	{
		ret = cub_valid_right_side(map, x, y + 1);
		if (ret == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	cub_valid_left_side(t_map *map, int x, int y)
{
	int	ret;

	ret = SUCCESS;
	if (map->map[y][x] == '1')
	{
		return (SUCCESS);
	}
	else if (map->map[y][x] != ' ')
	{
		perror("Error\nInvalid map");
		return (FAIL);
	}
	if (x + 1 < map->w && map->map[y][x + 1])
	{
		ret = cub_valid_left_side(map, x + 1, y);
		if (ret == FAIL)
			return (FAIL);
	}
	if (y + 1 < map->h && map->map[y + 1][x])
	{
		ret = cub_valid_left_side(map, x, y + 1);
		if (ret == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	cub_valid(t_map *map)
{
	int	y;
	int	ret;

	y = -1;
	ret = 0;
	while (++y < map->h)
	{
		ret = cub_valid_left_side(map, 0, y);
		if (ret == FAIL)
			return (FAIL);
		ret = cub_valid_right_side(map, map->w - 1, y);
		if (ret == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}
