/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/27 16:50:14 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_xline_minimap(t_mlx *mlx, float pixel_y,
		float pixel_size, int start_y)
{
	float	i;
	int		j;
	t_data	*minimap;
	float	pixel_x;

	j = 0;
	i = -(float)MINIMAP_SCALE / 2;
	minimap = &mlx->img_data[mlx->num_frame];
	while (j < mlx->minimap.w)
	{
		pixel_x = mlx->user.x + i;
		if (pixel_y < 0 || pixel_y >= mlx->map.h
			|| pixel_x < 0 || pixel_x >= mlx->map.w)
			my_mlx_pixel_put(minimap,
				j, start_y, MINIMAP_BG);
		else if (mlx->map.map[(int)pixel_y][(int)pixel_x] == '1')
			my_mlx_pixel_put(minimap,
				j, start_y, MINIMAP_WALL);
		else
			my_mlx_pixel_put(minimap,
				j, start_y, MINIMAP_FLOOR);
		
		if (pixel_y - HITBOX < mlx->user.y && mlx->user.y < pixel_y + HITBOX
			&& pixel_x - HITBOX < mlx->user.x && mlx->user.x < pixel_x + HITBOX)
			my_mlx_pixel_put(minimap, j, start_y, MINIMAP_USER);
		i += pixel_size;
		j++;
	}
}

/**
 * @brief Draw minimap
 * starting from x - 5, y - 5 as user position (x, y)
 * end from x + 5, y + 5 as user position (x, y)
 * draw movement speed 100 / WINHEIGHT - 1 pixel as MINIMAP_SCALE is 10
*/
void	draw_minimap_routine(void *in)
{
	t_minimap	*minimap;

	minimap = (t_minimap *)in;
	while (minimap->start_y > minimap->end_y)
	{
		draw_xline_minimap(minimap->mlx, minimap->pixel_y,
			minimap->pixel_size, minimap->start_y);
		minimap->start_y--;
		minimap->pixel_y += minimap->pixel_size;
	}
}

void	init_minimap(t_pic *minimap)
{
	minimap->h = WINWIDTH / MINIMAP_SCALE;
	minimap->w = WINWIDTH / MINIMAP_SCALE;
}
