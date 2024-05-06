/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:19:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 17:07:05 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	map_to_user(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < mlx->map.h)
	{
		x = -1;
		while (++x < mlx->map.w)
		{
			if (mlx->map.map[y][x] == 'N' || mlx->map.map[y][x] == 'S'
				|| mlx->map.map[y][x] == 'W' || mlx->map.map[y][x] == 'E')
			{
				init_user(&(mlx->user), (float)(x + 0.5),
					(float)(y + 0.5), mlx->map.map[y][x]);
				mlx->dda.cos_rot_speed = cos(mlx->user.rot_speed);
				mlx->dda.sin_rot_speed = sin(mlx->user.rot_speed);
				mlx->map.map[y][x] = '0';
				break ;
			}
		}
	}
}

//tmp
void	print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("map width: %d\n", map->w);
	printf("map height: %d\n", map->h);
	while (i < map->h)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}


int	cub_to_struct(char *file, t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open_file(file);
	line = read_cub(fd, mlx);
	if (line == NULL)
		ft_exit("No map in cub file");
	if (map_cub(line, fd, &(mlx->map)) == FAIL)
		ft_exit("Invalid map in cub file");
	close_file(fd);
	cub_dup_valid(mlx);
	cub_map_valid(&(mlx->map));
	map_to_user(mlx);
	print_map(&mlx->map);
	return (SUCCESS);
}
