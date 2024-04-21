/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/21 02:21:33 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * change 64 to img_w or set floor xpm to 64
*/
static void	draw_floor_pixel(t_mlx *graphic, t_floor *floor, int i)
{
	int	j;
	int	color;

	j = -1;
	while (++j < WINWIDTH)
	{
		floor->cell_x = (int)(floor->floor_x);
		floor->cell_y = (int)(floor->floor_y);
		floor->tx = (int)(64 * (floor->floor_x - floor->cell_x)) & (63);
		floor->ty = (int)(64 * (floor->floor_y - floor->cell_y)) & (63);
		// printf("tx: %d ty: %d\n", floor->tx, floor->ty);
		// printf("block pic: [%p]\n", &graphic->block.pic[FLOOR].data);
		floor->floor_x += floor->floor_step_x;
		floor->floor_y += floor->floor_step_y;
		color = my_mlx_pixel_get(&graphic->block.pic[FLOOR].data, floor->tx, floor->ty);
		my_mlx_pixel_put(&graphic->img_data[graphic->num_frame],
			j, WINHEIGHT - 1 - i, color);
	}
}

/**
 * z component added when calculating floor.p (current z position)
 * TODO: fix - wall doesn't get drawn over horizontal line (o)
 * fixed above by remove / 2 for i
 * 
*/
void	draw_floor_routine(void *arg)
{
	t_floor			*floor;
	t_user			*user;

	floor = arg;
	user = &floor->mlx->user;
	while (--floor->end_i >= floor->start_i)
	{
		floor->raydir_x_start = user->dir_x - user->plane_x;
		floor->raydir_y_start = user->dir_y - user->plane_y;
		floor->raydir_x_end = user->dir_x + user->plane_x;
		floor->raydir_y_end = user->dir_y + user->plane_y;
		floor->p = floor->end_i - (HALF_WINHEIGHT) + (WINWIDTH * user->zy); // adding z compomenet to make floor with z change
		floor->pos_z = 1.34 * WINHEIGHT * 0.5;
		floor->row_distance = floor->pos_z / floor->p;
		floor->floor_step_x = -floor->row_distance
			* (floor->raydir_x_end - floor->raydir_x_start) / (WINWIDTH);
		floor->floor_step_y = -floor->row_distance
			* (floor->raydir_y_end - floor->raydir_y_start) / (WINWIDTH);
		floor->floor_x = user->x - floor->row_distance * floor->raydir_x_start;
		floor->floor_y = user->y - floor->row_distance * floor->raydir_y_start;
		draw_floor_pixel(floor->mlx, floor, floor->end_i);
	}
	free(floor);
}

void	draw_floor_thread(t_mlx *graphic)
{
	int		i;
	t_floor	*floor;

	i = -1;
	start_wait_for_threads(&graphic->pool, graphic->num_threads);
	while (++i < graphic->num_threads)
	{
		floor = malloc(sizeof(t_floor));
		floor->mlx = graphic;
		floor->start_i = WINHEIGHT / graphic->num_threads * i;
		floor->end_i = WINHEIGHT / graphic->num_threads * (i + 1);
		if (i == graphic->num_threads - 1)
			floor->end_i = WINHEIGHT;
		add_task(&graphic->pool, create_task(draw_floor_routine, floor));
	}
	wait_for_threads(&graphic->pool);
}

int	game_loop(void *arg)
{
	t_mlx			*graphic;
	t_user			*user;
	size_t			cur_time;

	graphic = arg;
	user = &graphic->user;
	// printf("start loop\n");
	// cur_time = get_time_in_us();
	draw_floor_thread(graphic);
	// printf("time taken: [%lu]us\n", get_time_in_us() - cur_time);
	// while (++dda->cur_pixel_x < WINWIDTH)
	// {
	// 	init_data(dda, user, dda->cur_pixel_x);
	// 	perform_dda(dda, user, &graphic->map);
	// 	draw_walls(dda, graphic, user, &graphic->map);
	// }
	draw_wall_thread(graphic);
	update_sprite(graphic, user);
	display_frame(graphic);
	cur_time = get_time_in_us();
	// printf("fps: [%lu]\n", 1000000/(cur_time - graphic->time));
	graphic->time = cur_time;
	// printf("user->zx: [%f] user->zy: [%f]\n", user->zx, user->zy);
	return (0);
}
