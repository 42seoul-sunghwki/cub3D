/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_thread_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:29:34 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/26 20:30:06 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap_thread(t_mlx *graphic)
{
	t_minimap	*minimap;
	int			i;

	i = -1;
	start_wait_for_threads(&graphic->pool, graphic->num_threads);
	while (++i < graphic->num_threads)
	{
		minimap = malloc(sizeof(t_minimap));
		minimap->mlx = graphic;
		minimap->start_y = graphic->minimap.h / graphic->num_threads * i;
		minimap->end_y = graphic->minimap.h / graphic->num_threads * (i + 1);
		minimap->pixel_y = graphic->user.y - MINIMAP_SCALE / 2 + (float)MINIMAP_SCALE / graphic->num_threads * i;
		minimap->pixel_size = (float)1000 / WINHEIGHT;
		if (i == graphic->num_threads - 1)
			minimap->end_y = graphic->map.h;
		printf("start_y: %d end_y: %d pixel_y : %f\n", minimap->start_y, minimap->end_y, minimap->pixel_y);
		add_task(&graphic->pool, create_task(draw_minimap_routine, minimap));
	}
	wait_for_threads(&graphic->pool);
}
