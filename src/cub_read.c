/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:04:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 14:48:14 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_cub_helper(char *line, int fd, t_mlx *graphic)
{
	int		ret;

	ret = slice_cub(line, graphic, &(graphic->block));
	printf("*line : %s\n", line);
	if (ret == UNDEFINED)
	{
		printf("map_cub\n");
		if (map_cub(line, fd, &(graphic->map)) == FAIL)
			return (FAIL);
		else
			return (UNDEFINED);
	}
	return (ret);
}

int	read_cub(char *cub, t_mlx *graphic)
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
		line = ft_sanitize_enter(line);
		ret = read_cub_helper(line, fd, graphic);
		if (ret == FAIL)
		{
			close_file(fd);
			free(line);
			return (FAIL);
		}
		if (ret == UNDEFINED)
			break ;
		free(line);
	}
	close_file(fd);
	return (SUCCESS);
}
