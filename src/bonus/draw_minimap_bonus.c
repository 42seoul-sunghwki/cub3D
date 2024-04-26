/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/26 16:43:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_init_minimap(t_mlx *mlx)
{
	int		i;
	int		j;
	t_pic	*minimap;

	minimap = &(mlx->minimap);
	i = 0;
	while (i < minimap->w)
	{
		j = 0;
		while (j < minimap->h)
		{
			my_mlx_pixel_put(&(minimap->data), i, j, MINIMAP_BG);
			j++;
		}
		i++;
	}
}

static void	draw_xline_minimap(t_mlx *mlx, float pixel_y,
	float pixel_size, int start_y)
{
	int		i;
	int		j;
	float	pixel_x;

	if (pixel_y < 0 || pixel_y > mlx->map.h)
		return ;
	j = 0;
	i = -MINIMAP_SCALE / 2;
	while (j < mlx->minimap.w)
	{
		pixel_x = mlx->user.x - i;
		if (pixel_x < 0 || pixel_x > mlx->map.w)
			continue ;
		if (mlx->map.map[(int)pixel_x][(int)pixel_y] == '1')
			my_mlx_pixel_put(&(mlx->minimap.data),
				(int)j, (int)start_y, MINIMAP_WALL);
		else
			my_mlx_pixel_put(&(mlx->minimap.data),
				(int)j, (int)start_y, MINIMAP_FLOOR);
		i += pixel_size;
		j++;
	}
}

/**
 * @brief Draw minimap
 * starting from x - 5, y - 5 as user position (x, y)
 * end from x + 5, y + 5 as user position (x, y)
 * draw movement speed 1000 / WINHEIGHT - 1 pixel as MINIMAP_SCALE is 10
*/
void	draw_minimap(t_mlx *mlx)
{
	float	pixel_size;
	float	pixel_y;
	int		range;
	int		i;
	int		j;

	draw_init_minimap(mlx);
	pixel_size = 1000 / WINHEIGHT;
	range = MINIMAP_SCALE / 2;
	i = -range;
	j = 0;
	while (j < mlx->minimap.h)
	{
		pixel_y = mlx->user.y - i;
		if (pixel_y < 0 || pixel_y > mlx->map.h)
			continue ;
		draw_xline_minimap(mlx, pixel_y, pixel_size, j);
		i += pixel_size;
		j += 1;
	}
}
