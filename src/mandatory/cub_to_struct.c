/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:19:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 14:47:10 by minsepar         ###   ########.fr       */
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
				ft_exit("Invalid map in duplicate user");
			init_user(&(mlx->user), (float)(x + 0.5),
				(float)(y + 0.5), mlx->map.map[y][x]);
			mlx->map.map[y][x] = '0';
			*flag = 1;
		}
	}
}

static void	map_alloc(t_mlx *mlx)
{
	int	y;
	int	flag;

	y = -1;
	flag = 0;
	while (++y < mlx->map.h)
	{
		map_to_user_x(mlx, &flag, y);
	}
	if (flag != 1)
		ft_exit("Not user");
}

static void	check_cub_file_name(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len - 4 <= 0)
		ft_exit("Wrong cub file name");
	if (ft_strncmp(&file[len - 4], ".cub", 5) != 0)
		ft_exit("Wrong cub file name");
}

int	cub_to_struct(char *file, t_mlx *mlx)
{
	int		fd;
	char	*line;

	check_cub_file_name(file);
	fd = open_file(file);
	line = read_cub(fd, mlx);
	if (line == NULL)
		ft_exit("No map in cub file");
	if (map_cub(line, fd, &(mlx->map)) == FAIL)
		ft_exit("Invalid map in cub file");
	close_file(fd);
	cub_dup_valid(mlx);
	cub_map_valid(&(mlx->map));
	map_alloc(mlx);
	return (SUCCESS);
}
