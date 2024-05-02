/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:56:15 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/30 23:19:11 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	handle_mouse_click(int button, int x, int y, void *arg)
{
	t_mlx	*graphic;

	graphic = arg;
	printf("button: %d\n", button);
	printf("x: %d y: %d\n", x, y);
	if (button == LEFT_CLICK && graphic->user_state != STATE_DRINK)
	{
		graphic->weapon_start_frame = graphic->total_frame;
		if (graphic->pepsi_open == false)
		{
			play_sound(graphic, OPEN_AND_DRINK_SOUND);
			graphic->user_state = STATE_OPEN_AND_DRINK;
			graphic->pepsi_open = true;
		}
		else
		{
			play_sound(graphic, DRINK_SOUND);
			graphic->user_state = STATE_DRINK;
		}
	}
	return (0);
}
