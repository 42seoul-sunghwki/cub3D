/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/13 16:19:18 by sunghwki         ###   ########.fr       */
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
		{
			printf("Error\nNot input texture\n");
			exit(1);
		}
		if (ft_strncmp(mlx->block.pic[i].name,
				mlx->block.pic[j].name, size) == 0)
		{
			printf("Error\nDuplicate texture\n");
			exit(1);
		}
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
	{
		printf("Error\nDuplicate color\n");
		exit(1);
	}
}
