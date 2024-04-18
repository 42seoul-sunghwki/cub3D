/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/18 21:05:26 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	perform_dda(t_dda *dda, t_user *user, t_map *map)
{
	while (dda->collision_flag == false)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			user->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			user->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map->map[user->map_y][user->map_x] == '1')
			dda->collision_flag = true;
	}
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
}

void	calculate_texture_helper(t_dda *dda, t_user *user)
{
	if (dda->side == 0 )
	{
		dda->wall_pixel_x = user->y + dda->perp_wall_dist * dda->raydir_y;
		if (dda->raydir_x > 0)
			dda->texture_num = SOUTH;
		else
			dda->texture_num = NORTH;
	}
	else
	{
		dda->wall_pixel_x = user->x + dda->perp_wall_dist * dda->raydir_x;
		if (dda->raydir_y > 0)
			dda->texture_num = WEST;
		else
			dda->texture_num = EAST;
	}
}

static void	calculate_texture(t_mlx *graphic, t_dda *dda, t_user *user)
{
	t_pic	*texture;

	calculate_texture_helper(dda, user);
	texture = &graphic->block.pic[dda->texture_num];
	dda->wall_pixel_x -= floor(dda->wall_pixel_x);
	dda->texture_x = (int)(dda->wall_pixel_x * (float) texture->w);
	// printf("dda->texture_x: %d\n", dda->texture_x);
	if ((dda->side == 0 && dda->raydir_x > 0)
		|| (dda->side == 1 && dda->raydir_y < 0))
		dda->texture_x = texture->w - dda->texture_x - 1;
	dda->text_step = 1.0 * texture->h / dda->line_height;
	dda->text_pos = (dda->draw_start_y - ((WINHEIGHT) / 2 + WINWIDTH * user->zy)
			+ dda->line_height / 2) * dda->text_step;
}

/**
 * TODO: find a way to make realistic shade effect
 * TODO: block comes out to be 540 x 480 fix it to make it square
*/
static void	draw_walls(t_dda *dda, t_mlx *graphic, t_user *user, t_map *map)
{
	int		wall_index;
	float	half_line_height;

	(void) map;
	half_line_height = dda->line_height / 2;
	dda->line_height = (int)(WINHEIGHT * WALL_RATIO / dda->perp_wall_dist);
	dda->draw_start_y = -half_line_height + HALF_WINHEIGHT
		+ WINWIDTH * user->zy;
	if (dda->draw_start_y < 0)
		dda->draw_start_y = 0;
	dda->draw_end_y = half_line_height + HALF_WINHEIGHT + WINWIDTH * user->zy;
	if (dda->draw_end_y >= WINHEIGHT)
		dda->draw_end_y = WINHEIGHT - 1;
	wall_index = map->map[user->map_y][user->map_x] - '0';
	calculate_texture(graphic, dda, user);
	draw_vertical_line(graphic, dda);
}

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
 * TODO: fix - wall doesn't get drawn over horizontal line
*/
void	draw_floor(t_mlx *graphic)
{
	t_floor			floor;
	t_user			*user;
	int				i;

	i = WINHEIGHT / 2;
	user = &graphic->user;
	while (--i > 0)
	{
		floor.raydir_x_start = user->dir_x - user->plane_x;
		floor.raydir_y_start = user->dir_y - user->plane_y;
		floor.raydir_x_end = user->dir_x + user->plane_x;
		floor.raydir_y_end = user->dir_y + user->plane_y;
		floor.p = i - (HALF_WINHEIGHT) + (WINWIDTH * user->zy); // adding z compomenet to make floor with z change
		floor.pos_z = 1.34 * WINHEIGHT * 0.5;
		floor.row_distance = floor.pos_z / floor.p;
		floor.floor_step_x = -floor.row_distance
			* (floor.raydir_x_end - floor.raydir_x_start) / (WINWIDTH);
		floor.floor_step_y = -floor.row_distance
			* (floor.raydir_y_end - floor.raydir_y_start) / (WINWIDTH);
		floor.floor_x = user->x - floor.row_distance * floor.raydir_x_start;
		floor.floor_y = user->y - floor.row_distance * floor.raydir_y_start;
		draw_floor_pixel(graphic, &floor, i);
	}
}

int	game_loop(void *arg)
{
	t_dda			*dda;
	t_mlx			*graphic;
	t_user			*user;
	size_t			cur_time;

	graphic = arg;
	dda = &graphic->dda;
	dda->cur_pixel_x = -1;
	user = &graphic->user;
	// printf("start loop\n");
	draw_floor(graphic);
	while (++dda->cur_pixel_x < WINWIDTH)
	{
		init_data(dda, user, dda->cur_pixel_x);
		perform_dda(dda, user, &graphic->map);
		draw_walls(dda, graphic, user, &graphic->map);
	}
	update_sprite(graphic, user);
	display_frame(graphic);
	cur_time = get_time_in_us();
	// printf("fps: [%lu]\n", 1000000/(cur_time - graphic->time));
	graphic->time = cur_time;
	// printf("user->zx: [%f] user->zy: [%f]\n", user->zx, user->zy);
	return (0);
}
