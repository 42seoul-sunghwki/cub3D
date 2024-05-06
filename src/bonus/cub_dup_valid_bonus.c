/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 19:08:20 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	cub_dup_valid_img(t_mlx *mlx, int i, char *name)
{
	int	j;
	int	len;

	j = -1;
	len = ft_strlen(name);
	while (++j < i)
	{
		if (j == 4 || j == 5)
		{
			if (mlx->block.pic[j].name == NULL)
				continue ;
		}
		if (mlx->block.pic[j].name == NULL)
			ft_exit("Not input texture");
		if (ft_strncmp(name, mlx->block.pic[j].name, len) == 0)
			ft_exit("Duplicate texture");
	}
}

void	cub_dup_valid(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < IMG_COUNT)
	{
		if (i == FI || i == CI)
		{
			if (mlx->block.pic[i].name == NULL)
				continue ;
		}
		if (mlx->block.pic[i].name == NULL)
			ft_exit("Not input texture");
		cub_dup_valid_img(mlx, i, mlx->block.pic[i].name);
	}
	if (mlx->block.f_trgb == mlx->block.c_trgb)
		ft_exit("Duplicate color");
}
