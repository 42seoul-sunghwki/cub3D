/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:53:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 19:09:01 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pic	*init_pic(void)
{
	t_pic	*pic;

	pic = (t_pic *)malloc(sizeof(t_pic));
	if (!pic)
		return (NULL);
	pic->w = UNDEFINED;
	pic->h = UNDEFINED;
	pic->img = NULL;
	return (pic);
}

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

t_user	*init_user(void)
{
	t_user	*return_user;

	return_user = malloc(sizeof(t_user));
	ft_memset((void *) return_user, 0, sizeof(t_user));
	return_user->x = 1.0;
	return_user->y = 1.0;
	return_user->z = 48.0;
	return_user->map_x = 0;
	return_user->map_y = 0;
	return_user->dir_x = 1.0;
	return_user->dir_y = 0.0;
	return_user->plane_x = 0.0;
	return_user->plane_y = 0.66;
	return (return_user);
}
