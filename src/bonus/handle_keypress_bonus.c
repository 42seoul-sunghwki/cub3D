/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/01 00:37:04 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	on_escape(t_mlx *graphic)
{
	mlx_destroy_window(graphic->mlx, graphic->win);
	terminate_program(graphic);
}

static void	handle_key_space(t_user *user)
{
	if (user->flag & JUMP)
		return ;
	user->flag |= JUMP;
	user->z_velocity = 60;
}

int	handle_keypress(int keycode, void *arg)
{
	t_mlx	*graphic;
	t_user	*user;

	graphic = arg;
	user = &graphic->user;
	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		on_escape((t_mlx *)arg);
	else if (keycode == SPACE)
		handle_key_space(user);
	else if (keycode == ONE)
		graphic->change_weapon_num = keycode;
	else
		graphic->key_states[keycode] = true;
	return (SUCCESS);
}
