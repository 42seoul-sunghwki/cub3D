/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrow_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:10:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/22 23:41:26 by minsepar         ###   ########.fr       */
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

static void	calculate_new_displacement_xy(t_user *user, t_mlx *graphic,
	float ws_flag, float ad_flag)
{
	if (graphic->key_states[W] || graphic->key_states[S])
	{
		if (graphic->key_states[W])
			ws_flag *= -1;
		user->new_displacement_y += user->dir_y * ws_flag * user->move_speed;
		user->new_displacement_x += user->dir_x * ws_flag * user->move_speed;
	}
	if (graphic->key_states[A] || graphic->key_states[D])
	{
		if (graphic->key_states[D])
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
	if (user->flag & DIAGONAL)
	{
		ws_flag *= DIAGONAL_SCALE;
		ad_flag *= DIAGONAL_SCALE;
	}
	user->new_displacement_x = 0;
	user->new_displacement_y = 0;
	calculate_new_displacement_xy(user, graphic, ws_flag, ad_flag);
}

static void	check_diagonal(t_mlx *graphic, t_user *user)
{
	static int	arrows[] = {W, A, S, D};
	int			i;
	int			counter;

	user->flag &= ~DIAGONAL;
	i = -1;
	counter = 0;
	while (++i < 4)
	{
		if (graphic->key_states[arrows[i]])
			counter++;
	}
	if (counter == 2)
		user->flag |= DIAGONAL;
}

void	check_collision(t_mlx *graphic)
{
	t_user		*user;

	user = &graphic->user;
	check_diagonal(graphic, user);
	calculate_new_displacement(graphic);
	if (user->new_displacement_y <= 0)
		dir_y_check_n(&graphic->map, user);
	else
		dir_y_check_p(&graphic->map, user);
	if (user->new_displacement_x <= 0)
		dir_x_check_n(&graphic->map, user);
	else
		dir_x_check_p(&graphic->map, user);
}
