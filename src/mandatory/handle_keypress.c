/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/12 16:35:37 by minsepar         ###   ########.fr       */
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

void	check_collision(t_mlx *graphic, int keycode)
{
	float	new_displacement_y;
	float	new_displacement_x;
	int		flag;
	t_user	*user;
	t_map	*map;

	user = &graphic->user;
	map = &graphic->map;
	flag = -1;
	// printf("keycode: %d\n", keycode);
	if (keycode == 3)
		flag = 1;
	new_displacement_y = user->dir_y * flag * user->move_speed;
	new_displacement_x = user->dir_x * flag * user->move_speed;
	// printf("displacement x: [%f] displacement y: [%f]\n", new_displacement_x, new_displacement_y);
	if (new_displacement_y <= 0)
		dir_y_check_n(map, user, new_displacement_y);
	else
		dir_y_check_p(map, user, new_displacement_y);
	if (new_displacement_x <= 0)
		dir_x_check_n(map, user, new_displacement_x);
	else
		dir_x_check_p(map, user, new_displacement_x);
}

/**
 * TODO:	Use user hitbox radius to detect collision (X)
 * 
 * 			Using AABB instead. Using square box detection.
*/
// void	handle_down_arrow(t_mlx *graphic)
// {
// 	t_map	*map;
// 	t_user	*user;

// 	map = &graphic->map;
// 	user = &graphic->user;
// 	if (map->map[(int)(user->x - user->dir_x * user->move_speed)][(int)user->y]
// 		== '0')
// 	{
// 		printf("moved backward\n");
// 		user->x -= user->dir_x * user->move_speed;
// 	}
// 	if (map->map[(int)user->x][(int)(user->y - user->dir_y * user->move_speed)]
// 		== '0')
// 	{
// 		printf("moved backward\n");
// 		user->y -= user->dir_y * user->move_speed;
// 	}
// }

/**
 *
*/
// void	handle_up_arrow(t_mlx *graphic)
// {
// 	t_map	*map;
// 	t_user	*user;

// 	map = &graphic->map;
// 	user = &graphic->user;
// 	if (map->map[(int)(user->x + user->dir_x * user->move_speed)][(int)user->y]
// 		== '0')
// 	{
// 		printf("moved forward\n");
// 		user->x += user->dir_x * user->move_speed;
// 	}
// 	if (map->map[(int)user->x][(int)(user->y + user->dir_y * user->move_speed)]
// 		== '0')
// 	{
// 		printf("moved forward\n");
// 		user->y += user->dir_y * user->move_speed;
// 	}
// }

static void	on_escape(t_mlx *graphic)
{
	mlx_destroy_window(graphic->mlx, graphic->win);
	terminate_program(graphic);
}

int	handle_keypress(int keycode, void *arg)
{
	t_mlx		*graphic;
	static void	(*f[4])(t_mlx *, int) = {
		handle_left_arrow,
		handle_right_arrow,
		check_collision,
		check_collision
	};
	static void	(*f_linux[4])(t_mlx *, int) = {
		handle_left_arrow,
		check_collision,
		handle_right_arrow,
		check_collision
	};
	// if (keycode > 5000)
	// 	keyco
	graphic = arg;
	if (keycode == 53 || keycode == 65307)
		on_escape(graphic);
	if (keycode >= 123 && keycode <= 126)
	{
		keycode -= ARROW_OFFSET;
		f[keycode]((t_mlx *)arg, keycode);
	}
	else if (keycode >= 65361 && keycode <= 65364)
	{
		keycode -= 65361;
		f_linux[keycode]((t_mlx *)arg, keycode);
	}
	return (SUCCESS);
}
