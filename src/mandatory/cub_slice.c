/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:42:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/13 15:52:07 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	slice_wall_cub(char **split, t_mlx *mlx, t_block *block)
{
	static char	*wall[] = {"NO", "SO", "EA", "WE"};
	int			i;

	i = -1;
	while (++i < 4)
	{
		if (ft_strncmp(split[0], wall[i], 3) == 0)
		{
			if (split[1] == NULL)
				ft_exit("Wrong Input in Wall");
			if (check_img_cub(split, mlx, &(block->pic[i])) == FAIL)
				return (FAIL);
			return (SUCCESS);
		}
	}
	i = -1;
	while (split[0][++i])
	{
		if (split[0][i] != '1' && split[0][i] != ' ')
			ft_exit("Wrong File");
	}
	return (UNDEFINED);
}

static int	slice_color_cub(char **split, t_block *block)
{
	if (ft_strncmp(split[0], "F", 2) == 0)
	{
		if (block->f_trgb != -1)
			ft_exit("Duplicate Color");
		if (split[1] == NULL)
			ft_exit("Wrong Input in Color");
		block->f_trgb = color_cub(split);
		if (block->f_trgb == UNDEFINED)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "C", 2) == 0)
	{
		if (block->c_trgb != -1)
			ft_exit("Duplicate Color");
		if (split[1] == NULL)
			ft_exit("Wrong Input in Color");
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
	if (split[0] == NULL && ft_strlen(line) > 0)
		ft_exit("Space in files");
	if (split[0] == NULL || split[0][0] == '\0')
	{
		free_2d_ptr(split);
		return (SUCCESS);
	}
	if (slice_color_cub(split, block) == SUCCESS || \
		slice_wall_cub(split, mlx, block) == SUCCESS)
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
