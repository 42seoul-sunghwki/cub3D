/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_keypress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:47:36 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 14:56:19 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_new_displacement_xy(t_user *user, t_mlx *graphic,
	float ws_flag, float ad_flag)
{
	if (graphic->keycode == W || graphic->keycode == S)
	{
		if (graphic->keycode == W)
			ws_flag *= -1;
		user->new_displacement_y += user->dir_y * ws_flag * user->move_speed;
		user->new_displacement_x += user->dir_x * ws_flag * user->move_speed;
	}
	if (graphic->keycode == A || graphic->keycode == D)
	{
		if (graphic->keycode == D)
			ad_flag *= -1;
		user->new_displacement_y += -user->dir_x * ad_flag * user->move_speed;
		user->new_displacement_x += user->dir_y * ad_flag * user->move_speed;
	}
}

static void	calculate_new_displacement(t_mlx *graphic)
{
	t_user	*user;
	float	ws_flag;
	float	ad_flag;

	user = &graphic->user;
	ws_flag = -1;
	ad_flag = -1;
	user->new_displacement_x = 0;
	user->new_displacement_y = 0;
	calculate_new_displacement_xy(user, graphic, ws_flag, ad_flag);
}

void	check_collision(t_mlx *graphic)
{
	t_user		*user;

	user = &graphic->user;
	calculate_new_displacement(graphic);
	if (user->new_displacement_y <= 0)
		dir_y_check_n(&graphic->map, user, user->new_displacement_y);
	else
		dir_y_check_p(&graphic->map, user, user->new_displacement_y);
	if (user->new_displacement_x <= 0)
		dir_x_check_n(&graphic->map, user, user->new_displacement_x);
	else
		dir_x_check_p(&graphic->map, user, user->new_displacement_x);
}
