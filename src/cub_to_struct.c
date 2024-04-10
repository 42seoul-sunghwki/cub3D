/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:19:30 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 15:31:57 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_to_struct(char *file, t_mlx *mlx)
{
	int		fd;
	char	*line;
	
	fd = open_file(file);
	if (fd == UNDEFINED)
	{
		perror("Error\n");
		exit(1);
	}
	line = read_cub(fd, mlx);
	if (line == NULL)
	{
		perror("Error\nInvalid file");
		exit(1);
	}
	if (map_cub(line, fd, &(mlx->map)) == FAIL)
	{
		perror("Error\nInvalid map");
		exit(1);
	}
	close(fd);
	return (SUCCESS);
}
