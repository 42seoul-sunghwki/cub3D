/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:24:57 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/12 23:05:07 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	add_door_node(t_dda *dda)
{
	t_stack	*door_stack;
	t_list	*node;
	t_door	*door;
	t_mlx	*graphic;

	door_stack = &dda->door_stack;
	graphic = dda->mlx;
	door = get_door(graphic, dda->map_y, dda->map_x);
	if (!door)
	{
		printf("y: %d x: %d\n", dda->map_y, dda->map_x);
		terminate_program(graphic);
	}
	node = ft_lstnew(door);
	ft_lstadd_front(&door_stack->head, node);
	door_stack->size++;
}

static void	check_ray_collision(t_dda *dda, t_map *map)
{
	while (dda->collision_flag == false)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map->map[dda->map_y][dda->map_x] == '1')
			dda->collision_flag = true;
		if (is_open_door(map->map[dda->map_y][dda->map_x])
			|| is_close_door(map->map[dda->map_y][dda->map_x]))
		{
			add_door_node(dda);
			dda->changing_door = true;
		}
	}
}

static void	check_on_door(t_dda *dda, t_map *map)
{
	dda->changing_door = false;
	if (is_v_door(map->map[dda->map_y][dda->map_x]))
	{
		if (dda->side_dist_x / dda->delta_dist_x > 0.5)
			return (add_door_node(dda));
	}
	else
	{
		if (dda->side_dist_y / dda->delta_dist_y > 0.5)
			return (add_door_node(dda));
	}
	dda->changing_door = false;
}

void	perform_dda(t_mlx *graphic, t_dda *dda, t_map *map)
{
	(void) graphic;
	dda->changing_door = false;
	if (is_open_door(map->map[dda->map_y][dda->map_x])
		|| is_close_door(map->map[dda->map_y][dda->map_x]))
		check_on_door(dda, map);
	check_ray_collision(dda, map);
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
}
