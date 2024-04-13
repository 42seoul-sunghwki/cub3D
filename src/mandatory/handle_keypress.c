/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/13 17:47:07 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	on_escape(t_mlx *graphic)
{
	mlx_destroy_window(graphic->mlx, graphic->win);
	terminate_program(graphic);
}

int	handle_keypress(int keycode, void *arg)
{
	t_mlx		*graphic;
	static void	(*f[4])(t_mlx *, int) = {
		handle_left_arrow,
		handle_right_arrow,
		check_collision,
		check_collision
	};

	graphic = arg;
	if (keycode == 53)
		on_escape(graphic);
	if (keycode >= 123 && keycode <= 126)
	{
		keycode -= ARROW_OFFSET;
		f[keycode]((t_mlx *)arg, keycode);
	}
	return (SUCCESS);
}
