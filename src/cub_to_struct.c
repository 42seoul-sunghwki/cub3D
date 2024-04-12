/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:19:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/12 20:11:05 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_to_user(t_mlx *mlx)
{
	int	x;
	int	y;
	int	flag;

	y = -1;
	flag = 0;
	while (++y < mlx->map.h)
	{
		x = -1;
		while (++x < mlx->map.w)
		{
			if (mlx->map.map[y][x] == 'N' || mlx->map.map[y][x] == 'S'
				|| mlx->map.map[y][x] == 'W' || mlx->map.map[y][x] == 'E')
			{
				if (flag == 1)
				{
					printf("Error\nInvalid map\n");
					exit(1);
				}
				init_user(&(mlx->user), x, y, mlx->map.map[y][x]);
				mlx->map.map[y][x] = '0';
				flag = 1;
			}
		}
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
		printf("Error\nInvalid file");
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
