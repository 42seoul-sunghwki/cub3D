/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/26 14:56:43 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_init_minimap(t_mlx *mlx)
{
	int		i;
	int		j;
	t_pic	*minimap;

	minimap = &(mlx->minimap);
	minimap->data.
	i = 0;
	while (i < minimap->w)
	{
		j = 0;
		while (j < minimap->h)
		{
			if (i == 0 || i == minimap->w - 1 || j == 0 || j == minimap->h - 1)
				my_mlx_pixel_put(minimap, i, j, 0x00000000);
			else
				my_mlx_pixel_put(minimap, i, j, 0x33333333);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_mlx *mlx)
{
	int	**minimap;
	int	i;
	int	j;

	draw_init_minimap(mlx);
	i = 0;
	return (minimap);
}
