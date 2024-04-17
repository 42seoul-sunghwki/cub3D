/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:40:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/17 21:23:57 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_mouse_move_x(t_mlx *graphic, int displace_x)
{
	t_user	*user;
	t_dda	*dda;
	float	old_dir_x;
	float	old_plane_x;
	int		flag;

	flag = 1;
	if (displace_x < 0)
		flag = -1;
	graphic->dda.cos_rot_speed = cos(graphic->user.rot_speed * displace_x);
	graphic->dda.sin_rot_speed = sin(graphic->user.rot_speed * displace_x);
	user = &graphic->user;
	dda = &graphic->dda;
	old_dir_x = user->dir_x;
	old_plane_x = user->plane_x;
	user->dir_x = user->dir_x * dda->cos_rot_speed
		- user->dir_y * -dda->sin_rot_speed;
	user->dir_y = old_dir_x * -dda->sin_rot_speed
		+ user->dir_y * dda->cos_rot_speed;
	user->plane_x = user->plane_x * dda->cos_rot_speed
		- user->plane_y * -dda->sin_rot_speed;
	user->plane_y = old_plane_x * -dda->sin_rot_speed
		+ user->plane_y * dda->cos_rot_speed;
}

int	handle_mouse_move(int x, int y, void *arg)
{
	t_mlx	*graphic;

	graphic = (t_mlx *)arg;
	(void)arg;
	handle_mouse_move_x(graphic, x - HALF_WINWIDTH);
	mlx_mouse_move(graphic->win, HALF_WINWIDTH, HALF_WINHEIGHT);
	printf("y: [%d] x: [%d]\n", y, x);
	return (0);
}
