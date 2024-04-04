/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:04:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 19:21:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_cub(char **split)
{
	char	**rgb;
	int		ret;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(split[1], ',');
	if (!rgb)
		return (UNDEFINED);
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		perror("Error\nInvalid cub file");
		free_2d_ptr(rgb);
		return (UNDEFINED);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ret = create_trgb(0, r, g, b);
	free_2d_ptr(rgb);
	return (ret);
}

char	**split_line(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	if (split[0] == NULL)
	{
		free(split);
		return (NULL);
	}
	return (split);
}

int	check_img_cub(char **split, t_mlx *graphic, t_pic **org_img)
{
	t_pic	*pic;

	if (split[0] == NULL || split[1] == NULL || split[2] != NULL)
	{
		perror("Error\nInvalid cub file");
		return (FAIL);
	}
	pic = init_pic();
	if (!pic)
		return (FAIL);
	*org_img = pic;
	(*org_img)->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
			&(*org_img)->w, &(*org_img)->h);
	if (!(*org_img)->img)
	{
		free(pic);
		perror("Error\nInvalid cub file in img");
		return (FAIL);
	}
	return (SUCCESS);
}

int	read_cub(char *cub, t_mlx *graphic, t_map *map, t_block *block)
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
