/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 19:22:44 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	rotate_minimap(t_minimap *minimap,
	float pixel_x, float *rotate_x, float *rotate_y)
{
	float	vec_x;
	float	vec_y;
	float	rotate_vec_x;
	float	rotate_vec_y;

	vec_x = pixel_x - minimap->mlx->user.x;
	vec_y = minimap->pixel_y - minimap->mlx->user.y;
	rotate_vec_x = minimap->cos_user * vec_y
		+ minimap->sin_user * vec_x;
	rotate_vec_y = minimap->sin_user * vec_y
		- minimap->cos_user * vec_x;
	*rotate_x = rotate_vec_x + minimap->mlx->user.x;
	*rotate_y = rotate_vec_y + minimap->mlx->user.y;
}

static void	rotate_minimap_coord(t_minimap *minimap,
	t_coord *pixel, t_coord *rotate)
{
	float	vec_x;
	float	vec_y;
	float	rotate_vec_x;
	float	rotate_vec_y;

	vec_x = pixel->x - minimap->mlx->user.x;
	vec_y = pixel->y - minimap->mlx->user.y;
	rotate_vec_x = minimap->cos_user * vec_y
		+ minimap->sin_user * vec_x;
	rotate_vec_y = minimap->sin_user * vec_y
		- minimap->cos_user * vec_x;
	rotate->x = rotate_vec_x + minimap->mlx->user.x;
	rotate->y = rotate_vec_y + minimap->mlx->user.y;
}

void	count_user_coordinate(t_mlx *mlx, t_minimap *info)
{
	t_coord	coor;

	coor.x = mlx->user.x;
	coor.y = mlx->user.y;
	if (mlx->total_frame % UPDATE_COOR == 0)
	{
		rotate_minimap_coord(info, &coor,
			&mlx->user.last_coor[mlx->user.last_coor_idx]);
		mlx->user.last_coor_idx = (mlx->user.last_coor_idx + 1)
			% PREV_COOR_SIZE;
	}
}

static void	draw_rotate_minimap(t_mlx *mlx, t_coord *pixel,
		int minimap_x, int minimap_y)
{
	t_data	*minimap;
	int		tmp;
	int		get_trgb;

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
	else
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_FLOOR);
	if (minimap_x > mlx->minimap.w / 2 - NYANCAT_X
		&& minimap_x < mlx->minimap.w / 2 + NYANCAT_X
		&& minimap_y > mlx->minimap.h / 2 - NYANCAT_Y
		&& minimap_y < mlx->minimap.h / 2 + NYANCAT_Y)
	{
		get_trgb = my_mlx_pixel_get(&(mlx->block.bonus[BONUS_US].data),
			(int)((float)mlx->block.bonus[BONUS_US].w / (NYANCAT_X * 2) *
				(minimap_x - mlx->minimap.w / 2 + NYANCAT_X)), (int)((float)mlx->block.bonus[BONUS_US].h / (NYANCAT_Y * 2) * (minimap_y - mlx->minimap.h / 2 + NYANCAT_Y)));
		if (get_trgb > 0)
			my_mlx_pixel_put(minimap, minimap_x, minimap_y, get_trgb);
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
	t_coord		rotate_coord;
	float		pixel_x;
	int			i;

	minimap = (t_minimap *)in;
	while (minimap->start_y > minimap->end_y)
	{
		i = 0;
		minimap->start_x = minimap->mlx->minimap.w / 2 - sqrt(minimap->mlx->minimap.w * minimap->start_y - minimap->start_y * minimap->start_y);
		minimap->end_x = minimap->mlx->minimap.w - minimap->start_x;
		pixel_x = minimap->mlx->user.x - MINIMAP_SCALE / 2;
		while (i < minimap->end_x)
		{
			if (minimap->start_x > i)
			{
				i += 1;
				pixel_x += minimap->pixel_size;
				continue ;
			}
			rotate_minimap(minimap, pixel_x, &rotate_coord.x, &rotate_coord.y);
			draw_rotate_minimap(minimap->mlx, &rotate_coord, i, minimap->start_y);
			pixel_x += minimap->pixel_size;
			i += 1;
		}
		minimap->start_y--;
		minimap->pixel_y += minimap->pixel_size;
	}
	free(minimap);
}
