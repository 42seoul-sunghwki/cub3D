/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_user_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:29:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/30 21:44:03 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_weapon_pixel(t_weapon_thread *weapon_thread, t_pic *texture,
	int y, int x)
{
	t_mlx	*graphic;
	t_data	*frame;
	int		color;

	color = my_mlx_pixel_get(&texture->data,
			weapon_thread->tex_x, weapon_thread->tex_y);
	if (get_t(color) == 0xFF)
		return ;
	graphic = weapon_thread->mlx;
	frame = &graphic->img_data[graphic->num_frame];
	my_mlx_pixel_put(frame, x, y, color);
}
/**
 * TODO: either set w and h for weapon texture or set define for each weapon
*/
void	draw_weapon(void *arg)
{
	t_weapon_thread	*weapon_thread;
	t_pic			*texture;
	int				j;

	weapon_thread = arg;
	texture = weapon_thread->texture;
	while (--weapon_thread->draw_end >= weapon_thread->draw_start)
	{
		j = -1;
		weapon_thread->tex_x = (float) weapon_thread->draw_end
			/ WINWIDTH * 1920;
		weapon_thread->tex_x %= 1920;
		while (++j < WINHEIGHT)
		{
			weapon_thread->tex_y = (float) j / WINHEIGHT * 1080;
			weapon_thread->tex_y %= 1080;
			draw_weapon_pixel(weapon_thread,
				texture, j, weapon_thread->draw_end);
		}
	}
	free(weapon_thread);
}

void	draw_weapon_thread(t_mlx *graphic, t_pic *texture)
{
	t_weapon_thread	*weapon_thread;
	int				i;

	i = -1;
	start_wait_for_threads(&graphic->pool, graphic->num_threads);
	while (++i < graphic->num_threads)
	{
		weapon_thread = malloc(sizeof(t_weapon_thread));
		weapon_thread->mlx = graphic;
		weapon_thread->texture = texture;
		weapon_thread->draw_start = WINWIDTH / graphic->num_threads * i;
		weapon_thread->draw_end = WINWIDTH / graphic->num_threads * (i + 1);
		if (i == graphic->num_threads - 1)
			weapon_thread->draw_end = WINWIDTH;
		add_task(&graphic->pool, create_task(draw_weapon, weapon_thread));
	}
	wait_for_threads(&graphic->pool);
}

void	change_weapon(t_mlx *graphic)
{
	graphic->weapon_num = graphic->change_weapon_num;
	graphic->user_state = STATE_DRAW;
	graphic->weapon_start_frame = graphic->total_frame;
	if (graphic->weapon_num == 1)
		graphic->pepsi_open = 0;
}

void	change_state(t_mlx *graphic, int user_state)
{
	graphic->weapon_start_frame = graphic->total_frame;
	graphic->user_state = user_state;
}

void	weapon_render(t_mlx *graphic)
{
	t_sprite	*sprite;
	t_pic		*pic;
	int			*weapon_sprite;
	int			num_frame;

	weapon_sprite = graphic->weapon_sprite;
	sprite = &graphic->sprite[weapon_sprite[graphic->weapon_num]
		+ graphic->user_state];
	// num_frame = (graphic->total_frame - graphic->weapon_start_frame)
	// 	% sprite->num_img;
	num_frame = (graphic->total_frame - graphic->weapon_start_frame)
		% (sprite->num_img * sprite->fpm) / sprite->fpm;
	// printf("num_img: %d\n", sprite->num_img);
	pic = &sprite->img[num_frame];
	draw_weapon_thread(graphic, pic);
}

void	draw_user(t_mlx *graphic)
{
	t_sprite	*sprite;
	int			*weapon_sprite;
	int			user_state;

	weapon_sprite = graphic->weapon_sprite;
	user_state = graphic->user_state;
	sprite = &graphic->sprite[weapon_sprite[graphic->weapon_num] + user_state];
	if (graphic->change_weapon_num != graphic->weapon_num)
		change_weapon(graphic);
	else if ((user_state == STATE_DRINK || user_state == STATE_DRAW
			|| user_state == STATE_OPEN_AND_DRINK)
		&& graphic->total_frame - graphic->weapon_start_frame
		> sprite->num_img * sprite->fpm)
		change_state(graphic, STATE_IDLE);
	weapon_render(graphic);
}
