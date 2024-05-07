/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:11:40 by jacob             #+#    #+#             */
/*   Updated: 2024/05/07 15:40:56 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * TODO: norm, change tex_y ?
*/
static void	draw_sprite_pixel(t_sprite_info *sprite, t_mlx *graphic,
	int x, t_sprite_thread *sprite_thread)
{
	int		j;
	int		d;
	int		color;
	int		tex_y;
	t_data	*frame;

	j = sprite->draw_start_y - 1;
	frame = &graphic->img_data[graphic->num_frame];
	while (++j < sprite->draw_end_y)
	{
		d = (j - WINWIDTH * graphic->user.zy - graphic->user.z
				/ sprite_thread->node->distance)
			* 256 - (WINHEIGHT * 128) + (sprite->sprite_height) * 128;
		tex_y = ((d * sprite->texture->h) / sprite->sprite_height) / 256;
		if (tex_y < 0)
		{
			tex_y *= -1;
			tex_y %= sprite->sprite_height;
		}
		color = my_mlx_pixel_get(&sprite->texture->data,
				sprite_thread->tex_x, tex_y);
		if (get_t(color) != 0xFF)
			my_mlx_pixel_put(frame, x, j, color);
	}
}

void	draw_sprite(void *arg)
{
	int				i;
	t_sprite_thread	*sprite_thread;
	t_sprite_info	*sprite;

	sprite_thread = arg;
	sprite = &sprite_thread->mlx->sprite_info;
	i = sprite_thread->draw_start - 1;
	while (++i < sprite_thread->draw_end)
	{
		sprite_thread->tex_x = (256
				* (i - (-sprite->sprite_width / 2 + sprite->sprite_screen_x)))
			* sprite->texture->w / sprite->sprite_width / 256;
		if (sprite->transform_y > 0 && i > 0 && i < WINWIDTH
			&& sprite->transform_y < sprite_thread->mlx->z_buffer[i])
			draw_sprite_pixel(sprite, sprite_thread->mlx, i, sprite_thread);
	}
	free(sprite_thread);
}

void	project_sprite(t_mlx *graphic, t_user *user)
{
	t_sprite_node	*cur_sprite;
	t_sprite_vec	*vec;
	t_sprite		*sprite;
	int				i;
	int				frame_num;

	i = -1;
	vec = &graphic->sprite_vec;
	while (++i < vec->size)
	{
		cur_sprite = get_sprite(vec, i);
		// printf("sprite x: [%f] y: [%f]\n", cur_sprite->x, cur_sprite->y);
		sprite = &graphic->sprite[cur_sprite->sprite_type];
		frame_num = graphic->total_frame
			% (sprite->num_img * sprite->fpm) / sprite->fpm;
		calculate_sprite(&graphic->sprite_info, cur_sprite, user);
		draw_sprite_thread(graphic, &sprite->img[frame_num], cur_sprite);
	}
}

void	update_sprite(t_mlx *graphic, t_user *user)
{
	t_sprite_vec	*vec;

	vec = &graphic->sprite_vec;
	update_sprite_distance(graphic, user, vec);
	mergesort_sprite_list(graphic->sprite_vec.list, graphic->sprite_vec.size);
	project_sprite(graphic, user);
}
