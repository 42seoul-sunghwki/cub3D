/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacob <jacob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:11:40 by jacob             #+#    #+#             */
/*   Updated: 2024/04/12 15:33:51 by jacob            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprite(t_dda *dda, t_user *user, t_pic *sprite)
{
	int	i;

	i = -1;
	while (++i < NUM_SPRITE)
	{
		dda->sprite_order[i].index = i;
		dda->sprite_order[i].num
			= (user->x - sprite[i].w) * (user->x - sprite[i].w)
			+ (user->y - sprite[i].h) * (user->y - sprite[i].h);
	}
	sort_sprite_quick(dda->sprite_order, 0, NUM_SPRITE - 1);
}

void	project_sprite(t_dda *dda, t_user *user, t_pic *sprite)
{
	
}

void	draw_sprite(t_dda *dda, t_mlx *graphic, t_user *user)
{
	sort_sprite(dda, user, graphic->sprite);
	project_sprite(dda, user, graphic->sprite);
	
}
