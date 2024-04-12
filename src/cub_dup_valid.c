/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/12 21:04:33 by sunghwki         ###   ########.fr       */
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
		while (++j < 6)
		{
			if (mlx->block.pic[j].name == NULL)
				break ;
			if (ft_strncmp(mlx->block.pic[i].name,
					mlx->block.pic[j].name, size) == 0)
			{
				printf("Error\nDuplicate texture");
				exit(1);
			}
		}
	}
	if (mlx->block.f_trgb == mlx->block.c_trgb)
	{
		printf("Error\nDuplicate color");
		exit(1);
	}
}
