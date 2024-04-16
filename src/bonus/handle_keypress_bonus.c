/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/16 13:10:39 by codespace        ###   ########.fr       */
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
	t_mlx		*graphic;
	static void	(*f[4])(t_mlx *, int) = {
		handle_left_arrow,
		handle_right_arrow,
		check_collision,
		check_collision
	};
	static void (*f_l[4])(t_mlx *, int) = {
		handle_left_arrow,
		check_collision,
		handle_right_arrow,
		check_collision	
	};

	graphic = arg;
	// printf("keycode: %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
		on_escape(graphic);
	if (keycode >= 123 && keycode <= 126)
	{
		f[keycode]((t_mlx *)arg, keycode);
	}
	else if(keycode >= 65361 && keycode <= 65364)
	{
        f_l[keycode - 65361]((t_mlx *)arg, keycode);
	}
	return (SUCCESS);
}
