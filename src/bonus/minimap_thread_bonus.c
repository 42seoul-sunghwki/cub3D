/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_thread_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:29:34 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/28 18:43:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_minimap	*draw_minimap_thread_helper(t_minimap *info, t_mlx *graphic, int i)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	minimap->mlx = graphic;
	minimap->sin_user = info->sin_user;
	minimap->cos_user = info->cos_user;
	minimap->start_y = graphic->minimap.h
		- graphic->minimap.h / graphic->num_threads * i;
	minimap->end_y = graphic->minimap.h
		- graphic->minimap.h / graphic->num_threads * (i + 1);
	minimap->pixel_y = info->pixel_y
		+ (float)MINIMAP_SCALE / graphic->num_threads * i;
	minimap->pixel_size = info->pixel_size;
	if (i == graphic->num_threads - 1)
		minimap->end_y = 0;
	return (minimap);
}

void	draw_minimap_thread(t_mlx *graphic)
{
	t_minimap	*minimap;
	t_minimap	info;
	int			i;
	float		radius;

	i = -1;
	info.pixel_y = graphic->user.y - MINIMAP_SCALE / 2;
	info.pixel_size = (float)(MINIMAP_SCALE * MINIMAP_SCALE) / WINWIDTH;
	count_user_coordinate(graphic);
	radius = sqrt(graphic->user.dir_x * graphic->user.dir_x
			+ graphic->user.dir_y * graphic->user.dir_y);
	info.sin_user = graphic->user.dir_y / radius;
	info.cos_user = graphic->user.dir_x / radius;
	start_wait_for_threads(&graphic->pool, graphic->num_threads);
	while (++i < graphic->num_threads)
	{
		minimap = draw_minimap_thread_helper(&info, graphic, i);
		add_task(&graphic->pool, create_task(draw_minimap_routine, minimap));
	}
	wait_for_threads(&graphic->pool);
}
