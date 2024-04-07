/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:18 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/07 23:08:52 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_left_arrow(t_mlx *graphic)
{
	t_map	*map;
	t_user	*user;
	double	old_dir_x;
	double	old_plane_x;

	map = &graphic->map;
	user = &graphic->user;
	old_dir_x = user->dir_x;
	old_plane_x = user->plane_x;
	user->dir_x = user->dir_x * cos(user->rot_speed)
		- user->dir_y * sin(user->rot_speed);
	user->dir_y = old_dir_x * sin(user->rot_speed)
		+ user->dir_y * cos(user->rot_speed);
	user->plane_x = user->plane_x * cos(user->rot_speed)
		- user->plane_y * sin(user->rot_speed);
	user->plane_y = old_plane_x * sin(user->rot_speed)
		+ user->plane_y * cos(user->rot_speed);
}

void	handle_right_arrow(t_mlx *graphic)
{
	t_map	*map;
	t_user	*user;
	double	old_dir_x;
	double	old_plane_x;

	map = &graphic->map;
	user = &graphic->user;
	old_dir_x = user->dir_x;
	old_plane_x = user->plane_x;
	user->dir_x = user->dir_x * cos(-(user->rot_speed))
		- user->dir_y * sin(-(user->rot_speed));
	user->dir_y = old_dir_x * sin(-(user->rot_speed))
		+ user->dir_y * cos(-(user->rot_speed));
	user->plane_x = user->plane_x * cos(-(user->rot_speed))
		- user->plane_y * sin(-(user->rot_speed));
	user->plane_y = old_plane_x * sin(-(user->rot_speed))
		+ user->plane_y * cos(-(user->rot_speed));
}

void	handle_down_arrow(t_mlx *graphic)
{
	t_map	*map;
	t_user	*user;

	map = &graphic->map;
	user = &graphic->user;
	if (map->map[(int)(user->x - user->dir_x * user->move_speed)][(int)user->y]
		== '0')
	{
		printf("moved backward\n");
		user->x -= user->dir_x * user->move_speed;
	}
	if (map->map[(int)user->x][(int)(user->y - user->dir_y * user->move_speed)]
		== '0')
	{
		printf("moved backward\n");
		user->y -= user->dir_y * user->move_speed;
	}
}

void	handle_up_arrow(t_mlx *graphic)
{
	t_map	*map;
	t_user	*user;

	map = &graphic->map;
	user = &graphic->user;
	printf("up arrow\n");
	printf("x: [%d] y: [%d]\n", (int)(user->x + user->dir_x * user->move_speed), (int)user->y);
	printf("char: [%c]\n",
		map->map[(int)(user->x + user->dir_x * user->move_speed)][(int)user->y]);
	if (map->map[(int)(user->x + user->dir_x * user->move_speed)][(int)user->y]
		== '0')
	{
		printf("moved forward\n");
		user->x += user->dir_x * user->move_speed;
	}
	if (map->map[(int)user->x][(int)(user->y + user->dir_y * user->move_speed)]
		== '0')
	{
		printf("moved forward\n");
		user->y += user->dir_y * user->move_speed;
	}
}

static void	on_escape(t_mlx *graphic)
{
	mlx_destroy_window(graphic->mlx, graphic->win);
	terminate_program(graphic);
}

int	handle_keypress(int keycode, void *arg)
{
	t_mlx		*graphic;
	static void	(*f[4])(t_mlx *) = {
		handle_left_arrow,
		handle_right_arrow,
		handle_down_arrow,
		handle_up_arrow
	};

	graphic = arg;
	if (keycode == 53)
		on_escape(graphic);
	if (keycode >= 123 && keycode <= 126)
	{
		keycode -= ARROW_OFFSET;
		f[keycode]((t_mlx *)arg);
	}
	return (SUCCESS);
}
