/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/13 15:24:49 by sunghwki         ###   ########.fr       */
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

static void	cub_free_file_name(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (mlx->block.pic[i].name != NULL)
			free(mlx->block.pic[i].name);
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
	if (mlx->block.f_trgb == -1 || mlx->block.c_trgb == -1)
		ft_exit("Not initialize color");
	if (mlx->block.f_trgb == mlx->block.c_trgb)
		ft_exit("Duplicate color");
	cub_free_file_name(mlx);
}
