/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:42:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/13 12:14:17 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	slice_wall_cub(char **split, t_mlx *mlx, t_block *block)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
	{
		if (check_img_cub(split, mlx, &(block->pic[NO])) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "SO", 3) == 0)
	{
		if (check_img_cub(split, mlx, &(block->pic[SO])) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "WE", 3) == 0)
	{
		if (check_img_cub(split, mlx, &(block->pic)[WE]) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "EA", 3) == 0)
	{
		if (check_img_cub(split, mlx, &(block->pic)[EA]) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "FI", 3) == 0)
	{
		if (check_img_cub(split, mlx, &(block->pic)[FI]) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "CI", 3) == 0)
	{
		if (check_img_cub(split, mlx, &(block->pic)[CI]) == FAIL)
			return (FAIL);
	}
	else
		return (UNDEFINED);
	return (SUCCESS);
}

int	slice_color_cub(char **split, t_block *block)
{
	if (ft_strncmp(split[0], "F", 2) == 0)
	{
		block->f_trgb = color_cub(split);
		if (block->f_trgb == UNDEFINED)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "C", 2) == 0)
	{
		block->c_trgb = color_cub(split);
		if (block->c_trgb == UNDEFINED)
			return (FAIL);
	}
	else
		return (UNDEFINED);
	return (SUCCESS);
}

int	slice_cub(char *line, t_mlx *mlx, t_block *block)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (FAIL);
	if (split[0] == NULL || split[0][0] == '\0')
	{
		free_2d_ptr(split);
		return (SUCCESS);
	}
	if (slice_wall_cub(split, mlx, block) == SUCCESS)
	{
		free_2d_ptr(split);
		return (SUCCESS);
	}
	if (slice_color_cub(split, block) == SUCCESS)
	{
		free_2d_ptr(split);
		return (SUCCESS);
	}
	else
	{
		free_2d_ptr(split);
		return (UNDEFINED);
	}
}
