/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:47:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/21 00:51:53 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_wall_thread(t_mlx *graphic)
{
	t_dda	*dda;
	int		i;

	i = -1;
	start_wait_for_threads(&graphic->pool, graphic->num_threads);
	while (++i < graphic->num_threads)
	{
		dda = malloc(sizeof(t_dda));
		dda->mlx = graphic;
		dda->cur_pixel_x = WINWIDTH / graphic->num_threads * i;
		dda->end_pixel_x = WINWIDTH / graphic->num_threads * (i + 1);
		if (i == graphic->num_threads - 1)
			dda->end_pixel_x = WINWIDTH;
		add_task(&graphic->pool, create_task(draw_wall_routine, dda));
	}
	wait_for_threads(&graphic->pool);
}
