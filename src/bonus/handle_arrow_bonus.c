/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrow_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:10:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/22 21:42:29 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_left_arrow(t_mlx *graphic, int keycode)
{
	graphic->key_states[keycode] = true;
	printf("left_arrow [%d]\n", keycode);
}

void	handle_right_arrow(t_mlx *graphic, int keycode)
{
	graphic->key_states[keycode] = true;
	printf("right_arrow [%d]\n", keycode);
}

static void	calculate_new_displacement(t_mlx *graphic, float *new_displacement_y,
	float *new_displacement_x)
{
	t_user	*user;
	int		ws_flag;
	int		ad_flag;

	user = &graphic->user;
	if (graphic->key_states[W] || graphic->key_states[S])
	{
		ws_flag = -1;
		if (graphic->key_states[W])
			ws_flag = 1;
		*new_displacement_y = user->dir_y * ws_flag * user->move_speed;
		*new_displacement_x = user->dir_x * ws_flag * user->move_speed;
	}
	else
	{
		ad_flag = -1;
		if (graphic->key_states[D])
			ad_flag = 1;
		*new_displacement_y = -user->dir_x * ad_flag * user->move_speed;
		*new_displacement_x = user->dir_y * ad_flag * user->move_speed;
	}
}

void	check_collision(t_mlx *graphic)
{
	float	new_displacement_y;
	float	new_displacement_x;
	t_user	*user;

	user = &graphic->user;
	calculate_new_displacement(graphic, &new_displacement_y,
		&new_displacement_x);
	if (new_displacement_y <= 0)
		dir_y_check_n(&graphic->map, user, new_displacement_y);
	else
		dir_y_check_p(&graphic->map, user, new_displacement_y);
	if (new_displacement_x <= 0)
		dir_x_check_n(&graphic->map, user, new_displacement_x);
	else
		dir_x_check_p(&graphic->map, user, new_displacement_x);
}
