/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_thread_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:01:15 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/07 22:15:38 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprite_thread(t_mlx *graphic, t_pic *texture,
	t_sprite_node *cur_node)
{
	t_sprite_thread	*sprite_temp_info;
	t_sprite_info	*sprite;
	int				diff;
	int				i;

	sprite = &graphic->sprite_info;
	diff = sprite->draw_end_x - sprite->draw_start_x;
	i = -1;
	sprite->texture = texture;
	printf("%s\n", __func__);
	start_wait_for_threads(&graphic->pool, graphic->num_threads);
	while (++i < graphic->num_threads)
	{
		sprite_temp_info = malloc(sizeof(t_sprite_thread));
		sprite_temp_info->node = cur_node;
		sprite_temp_info->mlx = graphic;
		sprite_temp_info->draw_start = sprite->draw_start_x
			+ (diff / graphic->num_threads) * (i);
		sprite_temp_info->draw_end = sprite->draw_start_x
			+ (diff / graphic->num_threads) * (i + 1);
		if (i == graphic->num_threads - 1)
			sprite_temp_info->draw_end = sprite->draw_end_x;
		add_task(&graphic->pool, create_task(draw_sprite, sprite_temp_info));
	}
	wait_for_threads(&graphic->pool);
}
