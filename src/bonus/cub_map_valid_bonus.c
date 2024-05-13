/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_valid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:15:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/13 15:06:31 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	push_init_node(t_map *map, t_position posit,
		t_queue *queue, int direction)
{
	t_node	*tmp;
	char	*c;

	c = &map->map[posit.y][posit.x];
	if (posit.x >= map->w || posit.x < 0 || posit.y >= map->h || posit.y < 0)
		return ;
	if (c[0] == ' ' || c[0] == 0)
	{
		c[0] = 1;
		tmp = init_queue_node(posit.x, posit.y, direction);
		queue_push(queue, tmp);
	}
	else if (c[0] == 1 || c[0] == '1')
		return ;
	else
	{
		ft_exit("Invalid map\nIt isn't surround by 1");
	}
}

static void	pop_map_valid(t_map *map, t_queue *queue)
{
	static t_position	posit[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	t_position			next;
	t_node				*tmp;
	int					dir;

	while (1)
	{
		tmp = queue_pop(queue);
		if (tmp == NULL)
			return ;
		dir = tmp->direction;
		if (dir == LEFT)
		{
			next = (t_position){posit[DOWN].x + tmp->position.x,
				posit[DOWN].y + tmp->position.y};
			push_init_node(map, next, queue, DOWN);
		}
		else
		{
			next = (t_position){posit[dir - 1].x + tmp->position.x,
				posit[dir - 1].y + tmp->position.y};
			push_init_node(map, next, queue, dir - 1);
		}
		next = (t_position){posit[dir].x + tmp->position.x,
			posit[dir].y + tmp->position.y};
		push_init_node(map, next, queue, dir);
		if (dir == DOWN)
		{
			next = (t_position){posit[LEFT].x + tmp->position.x,
				posit[LEFT].y + tmp->position.y};
			push_init_node(map, next, queue, LEFT);
		}
		else
		{
			next = (t_position){posit[dir + 1].x + tmp->position.x,
				posit[dir + 1].y + tmp->position.y};
			push_init_node(map, next, queue, dir + 1);
		}
		free(tmp);
	}
}

static t_queue	*init_map_valid(t_map *map)
{
	int		x;
	int		y;
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->start = 0;
	queue->end = 0;
	queue->arr = (t_node **)malloc(sizeof(t_node *) * map->h * map->w);
	x = -1;
	while (++x < map->w)
	{
		push_init_node(map, (t_position){x, 0}, queue, DOWN);
		push_init_node(map, (t_position){x, map->h - 1}, queue, UP);
	}
	y = -1;
	while (++y < map->h)
	{
		push_init_node(map, (t_position){0, y}, queue, RIGHT);
		push_init_node(map, (t_position){map->w - 1, y}, queue, LEFT);
	}
	return (queue);
}

int	cub_map_valid(t_map *map)
{
	t_queue		*queue;

	queue = init_map_valid(map);
	pop_map_valid(map, queue);
	queue_delete(queue);
	free(queue->arr);
	free(queue);
	return (SUCCESS);
}
