/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:19:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/13 13:26:25 by sunghwki         ###   ########.fr       */
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



//int cub_to_st(char *file, t_mlx *mlx)
//{
//	int fd;
//	int i;
//	char *line;
//	char** split;
//	static char *cub[4] = {"NO", "SO", "WE", "EA"};
//	static char *cub2[2] = {"F", "C"};

//	fd = open_file(file);
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (!line)
//			break ;
//		ft_sanitize_enter(line);
//		split = ft_split(line, ' ');
//		if (!split)
//			return (FAIL);
//		if (split[0] == NULL || split[0][0] == '\0')
//		{
//			free(line);
//			free_2d_ptr(split);
//			continue ;
//		}
//		i = -1;
//		while (++i < 4)
//		{
//			if (ft_strncmp(split[0], cub[i], 3) == 0)
//			{
//				if (check_img_cub(split, mlx, &(mlx->block.pic[i])) == FAIL)
//					return (FAIL);
//				free(line);
//				free_2d_ptr(split);
//			}
//		}
//		i = -1;
//		while (++i < 2)
//		{
//			if (ft_strncmp(split[0], cub2[i], 2) == 0)
//			{
//				if (slice_color_cub(split, &(mlx->block)) == FAIL)
//					return (FAIL);
//				free(line);
//				free_2d_ptr(split);
//			}
//		}
//	}
//}
