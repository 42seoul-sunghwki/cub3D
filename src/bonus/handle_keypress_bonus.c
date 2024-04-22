/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/22 20:07:47 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	on_escape(t_mlx *graphic)
{
	mlx_destroy_window(graphic->mlx, graphic->win);
	terminate_program(graphic);
}

int	handle_keypress(int keycode, void *arg)
{
	// static void	(*f_l[4])(t_mlx *, int) = {
	// 	handle_left_arrow,
	// 	check_collision,
	// 	handle_right_arrow,
	// 	check_collision
	// };
	t_mlx	*graphic;

	graphic = arg;
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		on_escape((t_mlx *)arg);
	else
		graphic->key_states[keycode] = true;
	return (SUCCESS);
}
