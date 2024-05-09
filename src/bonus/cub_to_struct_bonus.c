/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:19:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 12:07:20 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
