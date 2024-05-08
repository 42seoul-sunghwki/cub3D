/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_sprite_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:10:26 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/08 16:09:56 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_sprite_helper(t_sprite_info *sprite,
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
	node->v_move_screen = (node->v_move / sprite->transform_y);
	sprite->sprite_screen_x = (int)((WINWIDTH / 2)
			* (1 + sprite->transform_x / sprite->transform_y));
	sprite->sprite_height = abs((int)(WINHEIGHT
				/ (sprite->transform_y)));
}

void	calculate_sprite(t_sprite_info *sprite,
	t_sprite_node *node, t_user *user)
{
	calculate_sprite_helper(sprite, node, user);
	sprite->draw_start_y = -(sprite->sprite_height / 2)
		+ WINHEIGHT / 2 + WINWIDTH * user->zy + user->z / node->distance;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = (sprite->sprite_height / 2)
		+ WINHEIGHT / 2 + WINWIDTH * user->zy + user->z / node->distance;
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
