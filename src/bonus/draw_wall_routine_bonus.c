/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_routine_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:05:29 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/12 15:43:10 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	*pop_list(t_list **list, int *size)
{
	t_list	*front;

	if (*size == 0)
		return (0);
	front = *list;
	*list = front->next;
	*size = *size - 1;
	return (front);
}

void	draw_wall_routine_bonus(t_dda *dda, t_mlx *graphic,
	t_map *map, t_user *user)
{
	t_list	*node;
	t_door	*door;

	init_data(dda, user, dda->cur_pixel_x);
	perform_dda(graphic, dda, map);
	draw_walls(dda, graphic, user, map);
	while (dda->door_stack.size > 0)
	{
		node = pop_list(&dda->door_stack.head, &dda->door_stack.size);
		door = node->content;
		init_data(dda, user, dda->cur_pixel_x);
		perform_door_dda(dda, map, door);
		if (dda->door_stack.size == 0)
			check_interaction_opendoor(graphic, dda, map);
		draw_walls(dda, graphic, user, map);
		free(node);
	}
	dda->cur_pixel_x++;
}

void	draw_wall_routine(void *arg)
{
	t_user	*user;
	t_mlx	*graphic;
	t_dda	*dda;
	t_map	*map;

	dda = arg;
	graphic = dda->mlx;
	user = &graphic->user;
	map = &graphic->map;
	while (dda->cur_pixel_x < dda->end_pixel_x)
	{
		draw_wall_routine_bonus(dda, graphic, map, user);
	}
	free(dda);
}
