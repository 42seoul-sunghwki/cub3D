/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/27 20:10:29 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_rotate_minimap(t_mlx *mlx, float pixel_x, float pixel_y,
		int minimap_x, int minimap_y)
{
	t_data	*minimap;
	int		tmp;
	int		get_trgb;

	minimap = &mlx->img_data[mlx->num_frame];
	if (pixel_y < 0 || pixel_y >= mlx->map.h
		|| pixel_x < 0 || pixel_x >= mlx->map.w)
	{
		get_trgb = my_mlx_pixel_get(minimap, minimap_x, minimap_y);
		tmp = blend_trgb(MINIMAP_BG, get_trgb);
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, tmp);
	}
	else if (mlx->map.map[(int)pixel_y][(int)pixel_x] == '1')
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_WALL);
	else
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_FLOOR);
	if (pixel_y - HITBOX < mlx->user.y && mlx->user.y < pixel_y + HITBOX
		&& pixel_x - HITBOX < mlx->user.x && mlx->user.x < pixel_x + HITBOX)
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_USER);
}

static void	rotate_minimap(t_minimap *minimap, float pixel_x, float *rotate_x, float *rotate_y)
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

void	draw_minimap_routine(void *in)
{
	t_minimap	*minimap;
	float		rotate_x;
	float		rotate_y;
	float		pixel_x;
	int			i;

	minimap = (t_minimap *)in;
	while (minimap->start_y > minimap->end_y)
	{
		i = 0;
		minimap->start_x = minimap->mlx->minimap.w / 2 - sqrt(minimap->mlx->minimap.w * minimap->start_y - minimap->start_y * minimap->start_y);
		minimap->end_x = minimap->mlx->minimap.w - minimap->start_x;
		i = 0;
		pixel_x = minimap->mlx->user.x - MINIMAP_SCALE / 2;
		while (i < minimap->end_x)
		{
			if (minimap->start_x > i)
			{
				i += 1;
				pixel_x += minimap->pixel_size;
				continue ;
			}
			rotate_minimap(minimap, pixel_x, &rotate_x, &rotate_y);
			//printf("i : %d, rotate_x : %f, rotate_y : %f\n", i, rotate_x, rotate_y);
			draw_rotate_minimap(minimap->mlx, rotate_x, rotate_y, i, minimap->start_y);
			pixel_x += minimap->pixel_size;
			i += 1;
		}
		minimap->start_y--;
		minimap->pixel_y += minimap->pixel_size;
	}
}

//static void	draw_xline_minimap(t_mlx *mlx, float pixel_y,
//			float pixel_size, int start_y)
//{
//	float	i;
//	int		j;
//	t_data	*minimap;
//	float	pixel_x;
//	float	rotate_x;
//	float	rotate_y;

//	j = 0;
//	i = -(float)MINIMAP_SCALE / 2;
//	minimap = &mlx->img_data[mlx->num_frame];
//	while (j < mlx->minimap.w)
//	{
//		pixel_x = mlx->user.x + i;
//		if (pixel_y < 0 || pixel_y >= mlx->map.h
//			|| pixel_x < 0 || pixel_x >= mlx->map.w)
//			my_mlx_pixel_put(minimap,
//				j, start_y, MINIMAP_BG);
//		else if (mlx->map.map[(int)pixel_y][(int)pixel_x] == '1')
//			my_mlx_pixel_put(minimap,
//				j, start_y, MINIMAP_WALL);
//		else
//			my_mlx_pixel_put(minimap,
//				j, start_y, MINIMAP_FLOOR);
//		if (pixel_y - HITBOX < mlx->user.y && mlx->user.y < pixel_y + HITBOX
//			&& pixel_x - HITBOX < mlx->user.x && mlx->user.x < pixel_x + HITBOX)
//			my_mlx_pixel_put(minimap, j, start_y, MINIMAP_USER);
//		i += pixel_size;
//		j++;
//	}
//}

///**
// * @brief Draw minimap
// * starting from x - 5, y - 5 as user position (x, y)
// * end from x + 5, y + 5 as user position (x, y)
// * draw movement speed 100 / WINHEIGHT - 1 pixel as MINIMAP_SCALE is 10
//*/
//void	draw_minimap_routine(void *in)
//{
//	t_minimap	*minimap;

//	minimap = (t_minimap *)in;
//	while (minimap->start_y > minimap->end_y)
//	{
//		draw_xline_minimap(minimap->mlx, minimap->pixel_y,
//			minimap->pixel_size, minimap->start_y);
//		minimap->start_y--;
//		minimap->pixel_y += minimap->pixel_size;
//	}
//}

void	init_minimap(t_pic *minimap)
{
	minimap->h = WINWIDTH / MINIMAP_SCALE;
	minimap->w = WINWIDTH / MINIMAP_SCALE;
}
