/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:40:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/26 19:14:51 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_mouse_move_x(t_mlx *graphic, int displace_x)
{
	t_user	*user;
	t_dda	*dda;
	float	old_dir_x;
	float	old_plane_x;

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

void	handle_mouse_move_z(t_mlx *graphic, int displace_z)
{
	t_user	*user;
	t_dda	*dda;
	float	old_zx;

	user = &graphic->user;
	dda = &graphic->dda;
	graphic->dda.cos_rot_speed = cos(graphic->user.rot_speed * displace_z);
	graphic->dda.sin_rot_speed = sin(graphic->user.rot_speed * displace_z);
	old_zx = user->zx;
	user->zx = user->zx * dda->cos_rot_speed
		- user->zy * -dda->sin_rot_speed;
	user->zy = old_zx * -dda->sin_rot_speed
		+ user->zy * dda->cos_rot_speed;
	if (user->zx < 0 && user->zy > 0)
	{
		user->zx = 0.0;
		user->zy = 1.0;
	}
	else if (user->zx < 0 && user->zy < 0)
	{
		user->zx = 0.0;
		user->zy = -1.0;
	}
	// printf("user->zy [%f]\n", user->zy);
}

int	handle_mouse_move(int x, int z, void *arg)
{
	t_mlx	*graphic;

	graphic = (t_mlx *)arg;
	(void)arg;
	//printf("handle_mouse_move");
	handle_mouse_move_x(graphic, x - HALF_WINWIDTH);
	handle_mouse_move_z(graphic, z - HALF_WINHEIGHT);
	//mac
	mlx_mouse_move(graphic->win, HALF_WINWIDTH, HALF_WINHEIGHT);
	//linux
	// mlx_mouse_move(graphic->mlx, graphic->win, HALF_WINWIDTH, HALF_WINHEIGHT);
	// printf("y: [%d] x: [%d]\n", z, x);
	return (0);
}
