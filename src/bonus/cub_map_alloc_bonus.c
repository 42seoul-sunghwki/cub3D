/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_alloc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:06:34 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 12:07:23 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	map_to_user(t_mlx *mlx, char **map, int x, int y)
{
	if (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		init_user(&(mlx->user), (float)(x + 0.5),
			(float)(y + 0.5), map[y][x]);
		mlx->dda.cos_rot_speed = cos(mlx->user.rot_speed);
		mlx->dda.sin_rot_speed = sin(mlx->user.rot_speed);
		map[y][x] = '0';
		return (1);
	}
	return (0);
}

static void	map_to_sprite_bonus(t_mlx *mlx, char **map, int x, int y)
{
	t_sprite_node	*node;

	if (map[y][x] == 'D')
	{
		if (mlx->sprite[DANCING_CAT].img != NULL)
		{
			node = create_sprite_node(x, y, DANCING_DOG, 0);
			push_sprite(&mlx->sprite_vec, node);
			map[y][x] = EMPTY;
		}
		else
			ft_exit("No valid sprite in dacing dog");
	}
}

static void	map_to_sprite(t_mlx *mlx, char **map, int x, int y)
{
	t_sprite_node	*node;

	if (map[y][x] == 'B')
	{
		if (mlx->sprite[DANCING_BEAR].img != NULL)
		{
			node = create_sprite_node(x, y, DANCING_BEAR, 0);
			push_sprite(&mlx->sprite_vec, node);
			map[y][x] = EMPTY;
		}
		else
			ft_exit("No valid sprite in dancing bear");
	}
	else if (map[y][x] == 'C')
	{
		if (mlx->sprite[DANCING_CAT].img != NULL)
		{
			node = create_sprite_node(x, y, DANCING_CAT, 0);
			push_sprite(&mlx->sprite_vec, node);
			map[y][x] = EMPTY;
		}
		else
			ft_exit("No valid sprite in dacing cat");
	}
	map_to_sprite_bonus(mlx, map, x, y);
}

void	map_alloc(t_mlx *mlx)
{
	int		x;
	int		y;
	char	**map;
	int		flag;

	y = -1;
	flag = 0;
	map = mlx->map.map;
	while (++y < mlx->map.h)
	{
		x = -1;
		while (++x < mlx->map.w)
		{
			if (map_to_user(mlx, map, x, y) == 1)
				flag = 1;
			map_to_sprite(mlx, map, x, y);
		}
	}
	if (flag != 1)
		ft_exit("Not user");
}
