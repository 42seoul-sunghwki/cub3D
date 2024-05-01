/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_nyan_tail_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:41:14 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/28 19:02:13 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_nyan_tail_routine(void *in)
{
	
}

void	draw_nyan_tail_thread(t_mlx *graphic)
{
	t_minimap	*minimap;
	t_minimap	info;
	int			i;
	int			j;
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
	j = 0;
	while (++i < graphic->num_threads)
	{
		minimap = draw_minimap_thread_helper(&info, graphic, i);
		minimap->coord_start = j;
		j += PREV_COOR_SIZE / graphic->num_threads;
		if (i == graphic->num_threads - 1)
			minimap->coord_end = PREV_COOR_SIZE;
		minimap->coord_end = j;
		add_task(&graphic->pool, create_task(draw_nyan_tail_routine, minimap));
	}
	wait_for_threads(&graphic->pool);
}
