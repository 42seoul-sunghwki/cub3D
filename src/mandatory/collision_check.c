/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:38:43 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 14:59:28 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_left_arrow(t_mlx *graphic, int keycode)
{
	t_user	*user;
	t_dda	*dda;
	float	old_dir_x;
	float	old_plane_x;

	(void) keycode;
	user = &graphic->user;
	dda = &graphic->dda;
	old_dir_x = user->dir_x;
	old_plane_x = user->plane_x;
	user->dir_x = user->dir_x * dda->cos_rot_speed
		- user->dir_y * dda->sin_rot_speed;
	user->dir_y = old_dir_x * dda->sin_rot_speed
		+ user->dir_y * dda->cos_rot_speed;
	user->plane_x = user->plane_x * dda->cos_rot_speed
		- user->plane_y * dda->sin_rot_speed;
	user->plane_y = old_plane_x * dda->sin_rot_speed
		+ user->plane_y * dda->cos_rot_speed;
}

void	handle_right_arrow(t_mlx *graphic, int keycode)
{
	t_dda	*dda;
	t_user	*user;
	float	old_dir_x;
	float	old_plane_x;

	(void) keycode;
	dda = &graphic->dda;
	user = &graphic->user;
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
