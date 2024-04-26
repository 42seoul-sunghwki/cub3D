/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/26 20:50:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//static void	draw_init_minimap(t_mlx *mlx)
//{
//	int		i;
//	int		j;
//	t_pic	*minimap;

//	minimap = &(mlx->minimap);
//	i = 0;
//	while (i < minimap->w)
//	{
//		j = 0;
//		while (j < minimap->h)
//		{
//			my_mlx_pixel_put(&(minimap->data), i, j, MINIMAP_BG);
//			j++;
//		}
//		i++;
//	}
//}

static void	draw_xline_minimap(t_mlx *mlx, float pixel_y,
	float pixel_size, int start_y)
{
	int		i;
	int		j;
	t_data	*minimap;
	float	pixel_x;

	if (pixel_y < 0 || pixel_y > mlx->map.h)
		return ;
	j = 0;
	i = -MINIMAP_SCALE / 2;
	minimap = &mlx->img_data[mlx->num_frame];
	while (j < mlx->minimap.w)
	{
		pixel_x = mlx->user.x - i;
		if (pixel_x < 0 || pixel_x > mlx->map.w)
			my_mlx_pixel_put(minimap,
				(int)j, (int)start_y, MINIMAP_BG);
		else if (mlx->map.map[(int)pixel_y][(int)pixel_x] == '1')
			my_mlx_pixel_put(minimap,
				(int)j, (int)start_y, MINIMAP_WALL);
		else
			my_mlx_pixel_put(minimap,
				(int)j, (int)start_y, MINIMAP_FLOOR);
		printf("pixel_x: %f pixel_y: %f\n", pixel_x, pixel_y);
		i += pixel_size;
		j++;
	}
}

void	draw_minimap_routine(void *in)
{
	t_minimap	*minimap;

	minimap = (t_minimap *)in;
	while (minimap->start_y < minimap->end_y)
	{
		printf("draw_minimap_routine start_y: %d end_y: %d pixel_y : %f\n",
			minimap->start_y, minimap->end_y, minimap->pixel_y);
		draw_xline_minimap(minimap->mlx, minimap->pixel_y,
			minimap->pixel_size, minimap->start_y);
		minimap->start_y++;
		minimap->pixel_y += minimap->pixel_size;
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

	//draw_init_minimap(mlx);
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
