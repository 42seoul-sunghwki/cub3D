/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacob <jacob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:57:58 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/11 22:47:12 by jacob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_time_in_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	display_frame(t_mlx *graphic)
{
	t_data	*data;

	// printf("frame_num: [%d]\n", graphic->num_frame);
	data = &graphic->img_data[graphic->num_frame];
	// printf("data->img [%p]\n", data->img);
	mlx_put_image_to_window(graphic->mlx, graphic->win, data->img, 0, 0);
	// printf("x: [%f] y: [%f]\n", graphic->user.x, graphic->user.y);
	graphic->num_frame ^= 1;
}
