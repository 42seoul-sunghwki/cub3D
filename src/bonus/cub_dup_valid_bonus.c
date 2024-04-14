/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/14 15:08:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_dup_valid_2(t_mlx *mlx, int i, int size)
{
	int	j;

	j = i;
	while (++j < 4)
	{
		if (mlx->block.pic[i].name == NULL || mlx->block.pic[j].name == NULL)
			ft_exit("Not input texture");
		if (ft_strncmp(mlx->block.pic[i].name,
				mlx->block.pic[j].name, size) == 0)
			ft_exit("Duplicate texture");
	}
}

void	cub_dup_valid(t_mlx *mlx)
{
	int	i;
	int	size;

	i = -1;
	while (++i < 4)
	{
		size = ft_strlen(mlx->block.pic[i].name);
		cub_dup_valid_2(mlx, i, size);
	}
	if (mlx->block.f_trgb == mlx->block.c_trgb)
		ft_exit("Duplicate color");
	i = 3;
	while (++i < 6)
	{
		if (mlx->block.pic[i].name == NULL)
			continue ;
		else
		{
			size = ft_strlen(mlx->block.pic[i].name);
			cub_dup_valid_2(mlx, i, size);
		}
	}
}
