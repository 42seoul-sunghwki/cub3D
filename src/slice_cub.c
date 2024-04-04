/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:42:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 19:21:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	slice_wall_cub(char **split, t_mlx *graphic, t_map *map, t_block *block)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
	{
		if (check_img_cub(split, graphic, &block->no) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "SO", 3) == 0)
	{
		if (check_img_cub(split, graphic, &block->so) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "WE", 3) == 0)
	{
		if (check_img_cub(split, graphic, &block->we) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "EA", 3) == 0)
	{
		if (check_img_cub(split, graphic, &block->ea) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	slice_f_c_cub(char **split, t_mlx *graphic, t_map *map, t_block *block)
{
	if (ft_strncmp(split[0], "FI", 3) == 0)
	{
		if (check_img_cub(split, graphic, &block->fi) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "CI", 3) == 0)
	{
		if (check_img_cub(split, graphic, &block->ci) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	slice_color_cub(char **split, t_mlx *graphic, t_map *map, t_block *block)
{
	if (ft_strncmp(split[0], "F", 3) == 0)
	{
		block->f_trgb = color_cub(split);
		if (block->f_trgb == UNDEFINED)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "C", 3) == 0)
	{
		block->c_trgb = color_cub(split);
		if (block->c_trgb == UNDEFINED)
			return (FAIL);
	}
}

int	slice_cub(char *line, t_mlx *graphic, t_map *map, t_block *block)
{
	char	**split;
	int		ret;

	ret = FAIL;
	split = split_line(line);
	if (!split)
		return (FAIL);
	if (split[0] == '\0')
	{
		free_2d_ptr(split);
		return (SUCCESS);
	}
	if (slice_wall_cub(split, graphic, map, block) == SUCCESS)
		ret = SUCCESS;
	else if (slice_f_c_cub(split, graphic, map, block) == SUCCESS)
		ret = SUCCESS;
	else if (slice_color_cub(split, graphic, map, block) == SUCCESS)
		ret = SUCCESS;
	else
		return (UNDEFINED); //add map slice
	free_2d_ptr(split);
	return (ret);
}
