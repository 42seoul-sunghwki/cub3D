/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_slice_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:42:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 11:24:12 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	slice_bonus_cub(char **split, t_mlx *mlx, t_block *block)
{
	static char	*bonus[1] = {"US"};
	int			i;

	i = -1;
	while (++i < 1)
	{
		if (ft_strncmp(split[0], bonus[i], 3) == 0)
		{
			if (check_img_cub(split, mlx, &(block->bonus[i])) == FAIL)
				return (FAIL);
			return (SUCCESS);
		}
	}
	i = -1;
	while (split[0][++i])
	{
		if (split[0][i] != '1' && split[0][i] != ' ')
			ft_exit("Wrong Img Name");
	}
	return (UNDEFINED);
}

static int	slice_wall_cub(char **split, t_mlx *mlx, t_block *block)
{
	static char	*wall[6] = {"NO", "SO", "EA", "WE", "CI", "FI"};
	int			i;

	i = -1;
	while (++i < 6)
	{
		if (ft_strncmp(split[0], wall[i], 3) == 0)
		{
			if (check_img_cub(split, mlx, &(block->pic[i])) == FAIL)
				return (FAIL);
			return (SUCCESS);
		}
	}
	return (UNDEFINED);
}

static int	slice_color_cub(char **split, t_block *block)
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
	if (slice_wall_cub(split, mlx, block) == SUCCESS || \
		slice_sprite_cub(split, mlx) == SUCCESS || \
		slice_color_cub(split, block) == SUCCESS || \
		slice_bonus_cub(split, mlx, block) == SUCCESS)
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
