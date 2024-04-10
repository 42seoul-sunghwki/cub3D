/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 16:33:57 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_dup_valid(t_mlx *mlx)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	while (++i < 4)
	{
		j = i;
		size = ft_strlen(mlx->block.pic[i].name);
		while (++j < 4)
		{
			if (ft_strncmp(mlx->block.pic[i].name,
					mlx->block.pic[j].name, size) == 0)
			{
				perror("Error\nDuplicate texture");
				exit(1);
			}
		}
	}
	if (mlx->block.f_trgb == mlx->block.c_trgb)
	{
		perror("Error\nDuplicate color");
		exit(1);
	}
}