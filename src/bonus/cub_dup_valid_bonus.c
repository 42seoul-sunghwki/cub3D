/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/08 11:21:32 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	cub_dup_valid_two_img(t_pic *org, t_pic *cmp)
{
	int	len;

	len = ft_strlen(org->name);
	if (ft_strncmp(org->name, cmp->name, len) == 0)
		ft_exit("Duplicate texture");
}

static void	cub_dup_valid_img(t_mlx *mlx, t_pic *cmp, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (j == 4 || j == 5)
		{
			if (mlx->block.pic[j].name == NULL)
				continue ;
		}
		if (mlx->block.pic[j].name == NULL)
			ft_exit("Not input texture");
		cub_dup_valid_two_img(&mlx->block.pic[j], cmp);
	}
}

static void	cub_img_name_clear(t_mlx *mlx)
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
		if (mlx->block.pic[i].name != NULL)
			free(mlx->block.pic[i].name);
	}
	if (mlx->block.bonus[0].name != NULL)
		free(mlx->block.bonus[0].name);
	i = -1;
	while (++i < NUM_SPRITE)
	{
		if (mlx->sprite[i].folder_name != NULL)
			free(mlx->sprite[i].folder_name);
	}
}

void	cub_dup_valid(t_mlx *mlx)
{
	int	i;

	i = -1;
	if (mlx->block.bonus[0].name == NULL)
		ft_exit("Not input minimap cat texture");
	while (++i < IMG_COUNT)
	{
		if (i == FI || i == CI)
		{
			if (mlx->block.pic[i].name == NULL)
				continue ;
		}
		if (mlx->block.pic[i].name == NULL)
			ft_exit("Not input texture");
		cub_dup_valid_img(mlx, &mlx->block.pic[i], i);
		cub_dup_valid_two_img(&mlx->block.pic[i], &mlx->block.bonus[0]);
	}
	if (mlx->block.f_trgb == mlx->block.c_trgb)
		ft_exit("Duplicate color");
	cub_dup_valid_sprite(mlx);
	cub_img_name_clear(mlx);
}
