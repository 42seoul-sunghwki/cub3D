/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:19:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/14 15:06:08 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_to_user_x(t_mlx *mlx, int *flag, int y)
{
	int	x;

	x = -1;
	while (++x < mlx->map.w)
	{
		if (mlx->map.map[y][x] == 'N' || mlx->map.map[y][x] == 'S'
			|| mlx->map.map[y][x] == 'W' || mlx->map.map[y][x] == 'E')
		{
			if (*flag == 1)
			{
				printf("Error\nInvalid map in duplicate user\n");
				exit(1);
			}
			init_user(&(mlx->user), x, y, mlx->map.map[y][x]);
			mlx->dda.cos_rot_speed = cos(mlx->user.rot_speed);
			mlx->dda.sin_rot_speed = sin(mlx->user.rot_speed);
			mlx->map.map[y][x] = '0';
			*flag = 1;
		}
	}
}

static void	map_to_user(t_mlx *mlx)
{
	int	y;
	int	flag;

	y = -1;
	flag = 0;
	while (++y < mlx->map.h)
	{
		map_to_user_x(mlx, &flag, y);
	}
}

int	cub_to_struct(char *file, t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open_file(file);
	line = read_cub(fd, mlx);
	if (line == NULL)
	{
		printf("Error\nInvalid file\n");
		exit(1);
	}
	if (map_cub(line, fd, &(mlx->map)) == FAIL)
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}
	close_file(fd);
	cub_dup_valid(mlx);
	cub_map_valid(&(mlx->map));
	map_to_user(mlx);
	return (SUCCESS);
}
