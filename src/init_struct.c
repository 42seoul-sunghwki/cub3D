/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:53:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 18:09:11 by sunghwki         ###   ########.fr       */
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
