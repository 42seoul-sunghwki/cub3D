/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_thread_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:29:34 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/27 14:41:42 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap_thread(t_mlx *graphic)
{
	t_minimap	*minimap;
	int			i;
	float		pixel_y_start;
	float		pixel_size;

	i = -1;
	pixel_y_start = graphic->user.y - MINIMAP_SCALE / 2;
	pixel_size = (float)(MINIMAP_SCALE * MINIMAP_SCALE) / WINWIDTH;
	start_wait_for_threads(&graphic->pool, graphic->num_threads);
	while (++i < graphic->num_threads)
	{
		minimap = malloc(sizeof(t_minimap));
		minimap->mlx = graphic;
		minimap->start_y = graphic->minimap.h - graphic->minimap.h / graphic->num_threads * i;
		minimap->end_y = graphic->minimap.h - graphic->minimap.h / graphic->num_threads * (i + 1);
		minimap->pixel_y = pixel_y_start + (float)MINIMAP_SCALE / graphic->num_threads * i;
		//printf("start_y : %d, end_y : %d, pixel_y: %f\n", minimap->start_y, minimap->end_y, minimap->pixel_y);
		minimap->pixel_size = pixel_size;
		if (i == graphic->num_threads - 1)
			minimap->end_y = 0;
		add_task(&graphic->pool, create_task(draw_minimap_routine, minimap));
	}
	wait_for_threads(&graphic->pool);
}
