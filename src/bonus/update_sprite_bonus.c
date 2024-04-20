/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:11:40 by jacob             #+#    #+#             */
/*   Updated: 2024/04/21 01:34:07 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_sprite(t_sprite_info *sprite,
	t_sprite_node *node, t_user *user)
{
	sprite->sprite_x = node->x - user->x;
	sprite->sprite_y = node->y - user->y;
	sprite->inv_det = 1.0 / ((user->plane_x * user->dir_y)
			- (user->dir_x * user->plane_y));
	sprite->transform_x = sprite->inv_det * (user->dir_y
			* sprite->sprite_x - user->dir_x * sprite->sprite_y);
	sprite->transform_y = sprite->inv_det * (-user->plane_y
			* sprite->sprite_x + user->plane_x * sprite->sprite_y);
	sprite->sprite_screen_x = (int)((WINWIDTH / 2)
			* (1 + sprite->transform_x / sprite->transform_y));
	sprite->sprite_height = abs((int)(WINHEIGHT
				/ (sprite->transform_y))) * 1.34;
	sprite->draw_start_y = -(sprite->sprite_height / 2) + WINHEIGHT / 2 + WINWIDTH * user->zy;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = (sprite->sprite_height / 2) + WINHEIGHT / 2 + WINWIDTH * user->zy;
	if (sprite->draw_end_y >= WINHEIGHT)
		sprite->draw_end_y = WINHEIGHT - 1;
	sprite->sprite_width = abs((int)(WINHEIGHT / sprite->transform_y));
	sprite->draw_start_x = -sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end_x >= WINWIDTH)
		sprite->draw_end_x = WINWIDTH - 1;
}

static void	draw_sprite_pixel(t_sprite_info *sprite, t_mlx *graphic,
	t_pic *texture, int x)
{
	int		j;
	int		d;
	int		color;
	t_data	*frame;

	j = sprite->draw_start_y - 1;
	frame = &graphic->img_data[graphic->num_frame];
	// printf("draw sprite pixel\n");
	while (++j < sprite->draw_end_y)
	{
		d = (j - WINWIDTH * graphic->user.zy) * 256 - (WINHEIGHT * 128) + sprite->sprite_height * 128;
		sprite->tex_y = ((d * texture->h) / sprite->sprite_height) / 256;
		// printf("%p\n", &texture->data);
		color = my_mlx_pixel_get(&texture->data, sprite->tex_x, sprite->tex_y);
		//color if it isn't invisible
		if (get_t(color) != 0xFF)
			my_mlx_pixel_put(frame, x, j, color);
	}
}

static void	draw_sprite(t_sprite_info *sprite,
	t_mlx *graphic, t_pic *texture)
{
	int		i;
	t_user	*user;

	user = &graphic->user;
	i = sprite->draw_start_x - 1;
	// printf("sprite->draw_start_x [%d]\n", sprite->draw_start_x);
	// printf("sprite->draw_end_x [%d]\n", sprite->draw_end_x);
	while (++i < sprite->draw_end_x)
	{
		// printf("draw_sprite\n");
		sprite->tex_x = (256
				* (i - (-sprite->sprite_width / 2 + sprite->sprite_screen_x)))
			* texture->w / sprite->sprite_width / 256;
		if (sprite->transform_y > 0 && i > 0 && i < WINWIDTH
			&& sprite->transform_y < graphic->z_buffer[i])
			draw_sprite_pixel(sprite, graphic, texture, i);
	}
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
	// printf("vec->size [%d]\n", vec->size);
	while (++i < vec->size)
	{
		cur_sprite = get_sprite(vec, i);
		// printf("sprite x: [%f] y: [%f]\n", cur_sprite->x, cur_sprite->y);
		sprite = &graphic->sprite[cur_sprite->sprite_type];
		frame_num = graphic->total_frame % (sprite->num_img * sprite->fpm) / sprite->fpm;
		// printf("start_frame: %ld, total_frame: [%ld] tex_num: %ld num_img %d\n", cur_sprite->start_frame, graphic->total_frame, frame_diff / sprite->fpm, sprite->num_img);
		calculate_sprite(&graphic->sprite_info ,cur_sprite, user);
		draw_sprite(&graphic->sprite_info, graphic, &sprite->img[frame_num]);
	}
}

void	update_sprite(t_mlx *graphic, t_user *user)
{
	t_sprite_vec	*vec;

	vec = &graphic->sprite_vec;
	//check for respawn? add sprite
	//delete sprite - dead sprite
	//update distance
	//sort
	//access or draw
	// printf("print sprite\n");
	project_sprite(graphic, user);
}
