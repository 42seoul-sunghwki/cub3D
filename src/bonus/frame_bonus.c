/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:57:58 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/05 14:50:40 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

size_t	get_time_in_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	display_frame(t_mlx *graphic)
{
	t_data	*data;

	data = &graphic->img_data[graphic->num_frame_render];
	mlx_put_image_to_window(graphic->mlx, graphic->win, data->img, 0, 0);
}

void	*render_thread(void *arg)
{
	t_mlx		*graphic;

	graphic = arg;
	while (1)
	{
		pthread_mutex_lock(&graphic->counter_mutex);
		while (graphic->frame_sync_counter < 1)
			pthread_cond_wait(&graphic->render_cond, &graphic->counter_mutex);
		pthread_mutex_unlock(&graphic->counter_mutex);
		if (graphic->pool.shutdown)
		{
			pthread_exit(NULL);
		}
		display_frame(graphic);
		pthread_mutex_lock(&graphic->counter_mutex);
		graphic->frame_sync_counter--;
		pthread_cond_signal(&graphic->render_cond);
		pthread_mutex_unlock(&graphic->counter_mutex);
		graphic->num_frame_render += 1;
		graphic->num_frame_render %= 3;
	}
}

void	init_frame_thread(t_mlx *graphic)
{
	pthread_mutex_init(&graphic->counter_mutex, NULL);
	pthread_cond_init(&graphic->render_cond, NULL);
	graphic->frame_sync_counter = 0;
	pthread_create(&graphic->render_thread, NULL, render_thread, graphic);
}
