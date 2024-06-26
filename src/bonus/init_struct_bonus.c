/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:53:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 21:42:04 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_block(t_block *block)
{
	int		i;

	i = -1;
	while (++i < 6)
	{
		init_pic(&(block->pic[i]));
	}
	block->f_trgb = UNDEFINED;
	block->c_trgb = UNDEFINED;
}

void	init_t_data(t_data *data)
{
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
}

void	init_pic(t_pic *pic)
{
	pic->w = 0;
	pic->h = 0;
	init_t_data(&(pic->data));
}

static void	init_user_helper(t_user *user, char pos)
{
	if (pos == 'N')
	{
		user->dir_y = 1.0;
		user->plane_x = 0.66;
	}
	else if (pos == 'S')
	{
		user->dir_y = -1.0;
		user->plane_x = -0.66;
	}
	else if (pos == 'W')
	{
		user->dir_x = -1.0;
		user->plane_y = 0.66;
	}
	else if (pos == 'E')
	{
		user->dir_x = 1.0;
		user->plane_y = -0.66;
	}
	memset(user->last_coor, 0, sizeof(t_coord) * PREV_COOR_SIZE);
}

void	init_user(t_user *user, float x, float y, char pos)
{
	int	i;

	i = 0;
	user->x = (double)x;
	user->y = (double)y;
	user->z = 0.0;
	user->dir_x = 0.0;
	user->dir_y = 0.0;
	user->plane_x = 0.0;
	user->plane_y = 0.0;
	user->move_speed = MOVE_SPEED;
	user->rot_speed = ROT_SPEED;
	user->zx = 1.0;
	user->zy = 0;
	user->flag = 0;
	user->z_velocity = 0;
	user->z_gravity = -4;
	init_user_helper(user, pos);
	while (i < PREV_COOR_SIZE)
	{
		user->last_coor[i].x = -1;
		user->last_coor[i].y = -1;
		i++;
	}
	user->last_coor_idx = 1;
}
