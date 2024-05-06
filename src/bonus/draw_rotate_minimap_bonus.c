/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rotate_minimap_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:48:42 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 21:49:38 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate_minimap(t_minimap *minimap,
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

void	rotate_minimap_coord(t_minimap *minimap,
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
