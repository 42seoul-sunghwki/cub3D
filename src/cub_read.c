/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:04:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 19:55:55 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_cub(char *cub, t_mlx *graphic, t_map *map, t_block *block)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open_file(cub);
	if (fd == UNDEFINED)
		return (FAIL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = slice_cub(line, graphic, block);
		if (ret == FAIL)
		{
			free(line);
			return (FAIL);
		}
		if (ret == UNDEFINED)
		{
			
		}
		free(line);
	}
	close_file(fd);
	return (SUCCESS);
}
