/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/08 16:07:13 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_rotate_minimap_blend(t_mlx *mlx, t_coord *pixel,
		int minimap_x, int minimap_y)
{
	t_data	*minimap;
	int		get_trgb;
	int		tmp;

	minimap = &mlx->img_data[mlx->num_frame];
	if (pixel->y < 0 || pixel->y >= mlx->map.h
		|| pixel->x < 0 || pixel->x >= mlx->map.w)
	{
		get_trgb = my_mlx_pixel_get(minimap, minimap_x, minimap_y);
		tmp = blend_trgb(MINIMAP_BG, get_trgb);
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, tmp);
	}
	else if (mlx->map.map[(int)pixel->y][(int)pixel->x] == '1')
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_WALL);
	else if (mlx->map.map[(int)pixel->y][(int)pixel->x] == 'V'
				|| mlx->map.map[(int)pixel->y][(int)pixel->x] == 'H')
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_DOOR);
	else
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_FLOOR);
}

static void	draw_rotate_minimap(t_mlx *mlx,
		int minimap_x, int minimap_y)
{
	t_data		*minimap;
	t_position	locate;
	int			get_trgb;

	minimap = &mlx->img_data[mlx->num_frame];
	if (minimap_x > mlx->minimap.w / 2 - NYANCAT_X
		&& minimap_x < mlx->minimap.w / 2 + NYANCAT_X
		&& minimap_y > mlx->minimap.h / 2 - NYANCAT_Y
		&& minimap_y < mlx->minimap.h / 2 + NYANCAT_Y)
	{
		locate.x = (int)((float)mlx->block.bonus[BONUS_US].w / (NYANCAT_X * 2)
				* (minimap_x - mlx->minimap.w / 2 + NYANCAT_X));
		locate.y = (int)((float)mlx->block.bonus[BONUS_US].h
				/ (NYANCAT_Y * 2)
				* (minimap_y - mlx->minimap.h / 2 + NYANCAT_Y));
		get_trgb = my_mlx_pixel_get(&(mlx->block.bonus[BONUS_US].data),
				locate.x, locate.y);
		if (get_trgb > 0)
			my_mlx_pixel_put(minimap, minimap_x, minimap_y, get_trgb);
	}
}

void	draw_minimap_xline(t_minimap *minimap, float pixel_x)
{
	t_coord	rotate_coord;
	int		i;

	i = 0;
	while (i < minimap->end_x)
	{
		if (minimap->start_x > i)
		{
			i += 1;
			pixel_x += minimap->pixel_size;
			continue ;
		}
		rotate_minimap(minimap, pixel_x, &rotate_coord.x, &rotate_coord.y);
		draw_rotate_minimap_blend(minimap->mlx, &rotate_coord,
			i, minimap->start_y);
		draw_rotate_minimap(minimap->mlx,
			i, minimap->start_y);
		pixel_x += minimap->pixel_size;
		i += 1;
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
	float		rotate_y;
	float		pixel_x;

	minimap = (t_minimap *)in;
	while (minimap->start_y > minimap->end_y)
	{
		rotate_y = sqrt(minimap->mlx->minimap.w * minimap->start_y
				- minimap->start_y * minimap->start_y);
		minimap->start_x = minimap->mlx->minimap.w / 2 - rotate_y;
		minimap->end_x = minimap->mlx->minimap.w - minimap->start_x;
		pixel_x = minimap->mlx->user.x - MINIMAP_SCALE / 2;
		draw_minimap_xline(minimap, pixel_x);
		minimap->start_y--;
		minimap->pixel_y += minimap->pixel_size;
	}
	free(minimap);
}
