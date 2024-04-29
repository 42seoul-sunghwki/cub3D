/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_user_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:29:27 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/29 20:56:25 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_weapon_pixel(t_weapon_thread *weapon_thread, t_pic *texture,
	int y, int x)
{
	t_mlx	*graphic;
	int		color;

	graphic = weapon_thread->mlx;
	color = my_mlx_pixel_get(&texture->data, x, y);
}

void	draw_weapon(void *arg)
{
	t_weapon_thread	*weapon_thread;
	t_pic			*texture;
	int				j;

	weapon_thread = arg;
	j = -1;
	texture = weapon_thread->texture;
	while (--weapon_thread->draw_end >= weapon_thread->draw_start)
	{
		weapon_thread->tex_x = weapon_thread->draw_end / WINWIDTH * texture->w;
		while (++j < WINHEIGHT)
		{
			weapon_thread->tex_y = j / WINHEIGHT * texture->h;
			
		}
	}
}

void	draw_weapon_thread(t_mlx *graphic, t_sprite *sprite, t_pic *texture)
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
		weapon_thread->draw_start = WINWIDTH * (i / graphic->num_threads);
		weapon_thread->draw_end = WINWIDTH * (i + 1) / graphic->num_threads;
		if (i == graphic->num_threads - 1)
			weapon_thread->draw_end = WINWIDTH;
		add_task(&graphic->pool, create_task(draw_weapon, weapon_thread));
	}
}

void	change_weapon(t_mlx *graphic)
{
	static int	weapon_sprite[] = {0, PEPSI_DRAW};
	t_sprite	*sprite;
	t_pic		*pic;

	graphic->weapon_num = graphic->change_weapon_num;
	sprite = &graphic->sprite[weapon_sprite[graphic->weapon_num]];
	pic = &sprite->img[0];
	draw_weapon_thread(graphic, sprite, pic);
}

void	draw_user(t_mlx *graphic)
{
	if (graphic->change_weapon_num != graphic->weapon_num)
		change_weapon(graphic);
}
