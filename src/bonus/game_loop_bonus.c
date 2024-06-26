/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/13 15:52:14 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mlx_sync_render(t_mlx *graphic)
{
	t_data	*data;

	data = &graphic->img_data[graphic->num_frame];
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img);
}

static void	game_loop_helper(t_mlx *graphic, t_user *user)
{
	(void) user;
	draw_floor_thread(graphic);
	draw_wall_thread(graphic);
	update_door(graphic);
	astar_thread(graphic);
	update_sprite(graphic, user);
	draw_minimap_thread(graphic);
	draw_user(graphic);
}

int	game_loop(void *arg)
{
	t_mlx			*graphic;
	t_user			*user;

	graphic = arg;
	user = &graphic->user;
	if (!(graphic->flag & MOUSE_START))
	{
		mlx_mouse_move(graphic->win, HALF_WINWIDTH, HALF_WINHEIGHT);
		graphic->flag |= MOUSE_START;
	}
	handle_keys_loop(graphic);
	mlx_sync_render(graphic);
	game_loop_helper(graphic, user);
	display_frame(graphic);
	graphic->num_frame += 1;
	graphic->num_frame %= 3;
	graphic->total_frame++;
	return (0);
}
