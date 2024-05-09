/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:38:43 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 14:37:17 by minsepar         ###   ########.fr       */
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
	printf("dda->cos %f\n", dda->cos_rot_speed);
	printf("dda->sin %f\n", dda->sin_rot_speed);
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

// static void	init_keycode(int *keycode, int *flag)
// {
// 	*flag = -1;
// 	if (*keycode == 3)
// 		*flag = 1;
// 	else if (*keycode > 3)
// 	{
// 		*keycode -= 65361;
// 		if (*keycode == 1)
// 			*flag = 1;
// 	}
// }

/**
 * checking collision for up and down arrow
*/
// void	check_collision(t_mlx *graphic, int keycode)
// {
// 	float	new_displacement_y;
// 	float	new_displacement_x;
// 	int		flag;
// 	t_user	*user;
// 	t_map	*map;

// 	init_keycode(&keycode, &flag);
// 	user = &graphic->user;
// 	map = &graphic->map;
// 	new_displacement_y = user->dir_y * flag * user->move_speed;
// 	new_displacement_x = user->dir_x * flag * user->move_speed;
// 	if (new_displacement_y <= 0)
// 		dir_y_check_n(map, user, new_displacement_y);
// 	else
// 		dir_y_check_p(map, user, new_displacement_y);
// 	if (new_displacement_x <= 0)
// 		dir_x_check_n(map, user, new_displacement_x);
// 	else
// 		dir_x_check_p(map, user, new_displacement_x);
// }
