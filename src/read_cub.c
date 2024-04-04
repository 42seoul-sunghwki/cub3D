/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:04:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 15:45:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	slice_cub(char *line, t_mlx *graphic, t_map *map, t_block *block)
{
	char	**split;
	t_pic	*pic;

	split = ft_split(line, ' ');
	if (!split)
		return (FAIL);
	pic = (t_pic *)malloc(sizeof(t_pic));
	if (!pic)
	{
		free(split);
		return (FAIL);
	}
	pic->w = IMG_W;
	pic->h = IMG_H;
	if (ft_strncmp(split[0], "NO", 3) == 0)
	{
		block->no = pic;
		block->no->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
				&block->no->w, &block->no->h);
	}
	else if (ft_strncmp(split[0], "SO", 3) == 0)
	{
		block->so = pic;
		block->so->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
				&block->so->w, &block->so->h);
	}
	else if (ft_strncmp(split[0], "WE", 3) == 0)
	{
		block->we = pic;
		block->we->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
				&block->we->w, &block->we->h);
	}
	else if (ft_strncmp(split[0], "EA", 3) == 0)
	{
		block->ea = pic;
		block->ea->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
				&block->ea->w, &block->ea->h);
	}
	else if (ft_strncmp(split[0], "F", 3) == 0)
	{
		
	}
	else if (ft_strncmp(split[0], "C", 3) == 0)
	{
		
	}
	else if (ft_strncmp(split[0], "FI", 3) == 0)
	{
		block->fi = pic;
		block->fi->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
				&block->fi->w, &block->fi->h);
	}
	else if (ft_strncmp(split[0], "CI", 3) == 0)
	{
		block->ci = pic;
		block->ci->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
				&block->ci->w, &block->ci->h);
	}
	else
	{
		
	}
	return (SUCCESS);
}

int	read_cub(char *cub, t_mlx graphic, t_map *map, t_block *block)
{
	int		fd;
	char	*line;

	fd = open_file(cub);
	if (fd == UNDEFINED)
		return (FAIL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (slice_cub(line, graphic, map, block) == FAIL)
		{
			free(line);
			return (FAIL);
		}
		free(line);
	}
	close_file(fd);
	return (SUCCESS);
}
