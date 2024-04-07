/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:53:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/05 23:42:08 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_block	*init_block(void)
{
	t_block	*block;

	block = (t_block *)malloc(sizeof(t_block));
	if (!block)
		return (NULL);
	block->no = NULL;
	block->so = NULL;
	block->we = NULL;
	block->ea = NULL;
	block->fi = NULL;
	block->ci = NULL;
	block->f_trgb = UNDEFINED;
	block->c_trgb = UNDEFINED;
	return (block);
}

t_pic	*init_pic(void)
{
	t_pic	*pic;

	pic = (t_pic *)malloc(sizeof(t_pic));
	if (!pic)
		return (NULL);
	pic->w = IMG_W;
	pic->h = IMG_H;
	pic->img = NULL;
	return (pic);
}

void	init_user(t_user *user)
{
	user->x = 5.0;
	user->y = 5.0;
	user->z = 48.0;
	user->map_x = 0;
	user->map_y = 0;
	user->dir_x = 1.0;
	user->dir_y = 1.0;
	user->plane_x = 1.0;
	user->plane_y = -1.0;
	user->move_speed = 0.05;
	user->rot_speed = 0.02;
}
