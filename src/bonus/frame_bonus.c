/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:57:58 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/10 20:06:27 by minsepar         ###   ########.fr       */
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

	data = &graphic->img_data[graphic->num_frame];
	// data = &graphic->img_data[0];
	mlx_put_image_to_window(graphic->mlx, graphic->win, data->img, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, graphic->win);
}
