/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/10 15:36:39 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mlx_sync_render(t_mlx *graphic)
{
	t_data	*data;

	data = &graphic->img_data[graphic->num_frame];
	// mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img);
}

static void	game_loop_helper(t_mlx *graphic, t_user *user)
{
	draw_floor_thread(graphic);
	draw_wall_thread(graphic);
	update_door(graphic);
	astar_thread(graphic);
	update_sprite(graphic, user);
	draw_minimap_thread(graphic);
	draw_user(graphic);
}

int	game_loop(void *arg)
{
	t_mlx			*graphic;
	t_user			*user;
	static size_t			total_calc_frame = 0;

	graphic = arg;
	user = &graphic->user;
	pthread_mutex_lock(&graphic->counter_mutex);
	while (graphic->frame_sync_counter >= 1)
		pthread_cond_wait(&graphic->render_cond, &graphic->counter_mutex);
	pthread_mutex_unlock(&graphic->counter_mutex);
	handle_keys_loop(graphic);
	mlx_sync_render(graphic);
	game_loop_helper(graphic, user);
	pthread_mutex_lock(&graphic->counter_mutex);
	graphic->frame_sync_counter++;
	graphic->num_frame += 1;
	graphic->num_frame %= 3;
	total_calc_frame++;
	pthread_cond_signal(&graphic->render_cond);
	pthread_mutex_unlock(&graphic->counter_mutex);
	graphic->total_frame++;
	return (0);
}
