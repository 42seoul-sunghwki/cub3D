/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 15:05:23 by sunghwki         ###   ########.fr       */
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
	static void	(*f[2])(t_mlx *, int) = {handle_left_arrow, handle_right_arrow};

	graphic = arg;
	if (keycode == 53)
		on_escape(graphic);
	if (keycode == 123 || keycode == 124)
	{
		keycode -= ARROW_OFFSET;
		f[keycode]((t_mlx *)arg, keycode);
	}
	else if ((keycode >= A && keycode <= D) || keycode == W)
	{
		graphic->keycode = keycode;
		check_collision(graphic);
	}
	return (SUCCESS);
}
