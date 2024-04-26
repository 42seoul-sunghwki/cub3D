/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/26 12:23:54 by sunghwki         ###   ########.fr       */
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

//static void	cub_dup_valid_sprite(t_mlx *mlx, int i, char *name)
//{
//	int	j;
//	int	len;

//	j = -1;
//	len = ft_strlen(name);
//	while (++j < i)
//	{
//		if (mlx->sprite[j].img == NULL || mlx->sprite[j].img->name == NULL)
//			ft_exit("Not input sprite");
//		if (ft_strncmp(name, mlx->sprite[j].img->name, len) == 0)
//			ft_exit("Duplicate sprite");
//	}
//}

void	cub_dup_valid(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (i == 4 || i == 5)
		{
			if (mlx->block.pic[i].name == NULL)
				continue ;
		}
		if (mlx->block.pic[i].name == NULL)
			ft_exit("Not input texture");
		cub_dup_valid_img(mlx, i, mlx->block.pic[i].name);
		//cub_dup_valid_sprite(mlx, 4, mlx->block.pic[i].name); //tmp remove
	}
	//i = -1;
	//while (++i < 4)
	//{
	//	if (mlx->sprite[i].img == NULL)
	//		ft_exit("Not input sprite");
	//	cub_dup_valid_img(mlx, 6, mlx->sprite[i].img->name);
	//	cub_dup_valid_sprite(mlx, i, mlx->sprite[i].img->name);
	//}
	if (mlx->block.f_trgb == mlx->block.c_trgb)
		ft_exit("Duplicate color");
}
