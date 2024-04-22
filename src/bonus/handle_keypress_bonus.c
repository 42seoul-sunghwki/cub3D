/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/22 22:46:14 by minsepar         ###   ########.fr       */
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
	t_mlx	*graphic;
	t_user	*user;

	graphic = arg;
	user = &graphic->user;
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		on_escape((t_mlx *)arg);
	else if (user->flag & JUMP)
	{
		printf("flag: %d\n", user->flag);
		return (SUCCESS);
	}
	else
		graphic->key_states[keycode] = true;
	return (SUCCESS);
}
