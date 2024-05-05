/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:33:29 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/02 23:47:21 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_sprite_fpm(t_mlx *graphic)
{
	graphic->sprite[DANCING_BEAR].fpm = 2;
	graphic->sprite[DANCING_DOG].fpm = 2;
	graphic->sprite[DANCING_CAT].fpm = 2;
	graphic->sprite[PEPSI_DRAW].fpm = 2;
	graphic->sprite[PEPSI_IDLE].fpm = 2;
	graphic->sprite[PEPSI_DRINK].fpm = 2;
	graphic->sprite[PEPSI_OPEN_AND_DRINK].fpm = 2;
	graphic->sprite[PEPSI_WALK].fpm = 2;
	graphic->sprite[PEPSI_RUN].fpm = 2;
	graphic->sprite[DOOR_CLOSE].fpm = 2;
}
