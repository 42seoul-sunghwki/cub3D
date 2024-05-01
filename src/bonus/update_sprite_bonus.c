/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:11:40 by jacob             #+#    #+#             */
/*   Updated: 2024/05/01 16:54:44 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_sprite(t_sprite_info *sprite,
	t_sprite_node *node, t_user *user, t_mlx *graphic)
{
	(void) graphic;

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
	sprite->draw_start_y = -(sprite->sprite_height / 2) + WINHEIGHT / 2 + WINWIDTH * user->zy + user->z / node->distance;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	// printf("node->distance: %f\n", node->distance);
	sprite->draw_end_y = (sprite->sprite_height / 2) + WINHEIGHT / 2 + WINWIDTH * user->zy + user->z / node->distance;
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
	int x, t_sprite_thread *sprite_thread)
{
	int		j;
	int		d;
	int		color;
	int		tex_y;
	t_data	*frame;

	j = sprite->draw_start_y - 1;
	frame = &graphic->img_data[graphic->num_frame];
	// printf("draw sprite pixel\n");
	while (++j < sprite->draw_end_y)
	{
		d = (j - WINWIDTH * graphic->user.zy - graphic->user.z /
				sprite_thread->node->distance) * 256 - (WINHEIGHT * 128) + 
			(sprite->sprite_height) * 128;
		tex_y = ((d * sprite->texture->h) / sprite->sprite_height) / 256;
		// printf("%p\n", &texture->data);
		color = my_mlx_pixel_get(&sprite->texture->data,
			sprite_thread->tex_x, tex_y);
		//color if it isn't invisible
		if (get_t(color) != 0xFF)
			my_mlx_pixel_put(frame, x, j, color);
	}
}

void	draw_sprite(void *arg)
{
	int				i;
	t_user			*user;
	t_sprite_thread	*sprite_thread;
	t_sprite_info	*sprite;

	sprite_thread = arg;
	user = &sprite_thread->mlx->user;
	sprite = &sprite_thread->mlx->sprite_info;
	i = sprite_thread->draw_start - 1;
	// printf("sprite->draw_start_x [%d]\n", sprite->draw_start_x);
	// printf("sprite->draw_end_x [%d]\n", sprite->draw_end_x);
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
	// printf("vec->size [%d]\n", vec->size);
	while (++i < vec->size)
	{
		cur_sprite = get_sprite(vec, i);
		// printf("sprite x: [%f] y: [%f]\n", cur_sprite->x, cur_sprite->y);
		sprite = &graphic->sprite[cur_sprite->sprite_type];
		frame_num = graphic->total_frame
			% (sprite->num_img * sprite->fpm) / sprite->fpm;
		// printf("start_frame: %ld, total_frame: [%ld] tex_num: %ld num_img %d\n", cur_sprite->start_frame, graphic->total_frame, frame_diff / sprite->fpm, sprite->num_img);
		calculate_sprite(&graphic->sprite_info, cur_sprite, user, graphic);
		draw_sprite_thread(graphic, &sprite->img[frame_num], cur_sprite);
		// draw_sprite(&graphic->sprite_info, graphic, &sprite->img[frame_num]);
	}
}

void	update_sprite(t_mlx *graphic, t_user *user)
{
	t_sprite_vec	*vec;
	int				i;

	vec = &graphic->sprite_vec;
	//check for respawn? add sprite
	//delete sprite - dead sprite
	//update distance
	jps(graphic);
	i = 0;
	while (i < vec->size)
	{
		sanitize_p_queue(&vec->list[i]->open_list);
		sanitize_p_queue(&vec->list[i]->close_list);
	}
	update_sprite_distance(graphic, user, vec);
	//sort
	//access or draw
	// printf("print sprite\n");
	project_sprite(graphic, user);
}
