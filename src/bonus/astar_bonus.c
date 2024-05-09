/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:23:18 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 13:22:07 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

int	check_halt_condition(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->w
		|| y >= map->h || map->map[y][x] == '1'
		|| map->map[y][x] == 'V' || map->map[y][x] == 'H')
	{
		return (true);
	}
	return (false);
}

int	check_map_range(t_map *map, t_position *position)
{
	if (position->x < 0 || position->y < 0
		|| position->x >= map->w || position->y >= map->h)
	{
		printf("out of map range\n");
		return (true);
	}
	return (false);
}

int	find_target(t_p_queue *list, t_position *position)
{
	int	i;

	i = 0;
	while (++i < list->size)
	{
		if (list->arr[i]->position.x == position->x
			&& list->arr[i]->position.y == position->y)
		{
			return (i);
		}
	}
	return (0);
}

void	astar_input(t_mlx *mlx, t_sprite_node *node,
		t_node *parent, t_position *tmp)
{
	t_coord	user;
	t_node	*in;

	user.x = mlx->user.x;
	user.y = mlx->user.y;
	if (check_halt_condition(tmp->x, tmp->y, &mlx->map) == false)
	{
		if (find_target(&node->close_list, tmp) == 0)
		{
			if (find_target(&node->open_list, tmp) == 0)
			{
				in = init_node(parent, tmp, &user, 5);
				in->next = parent;
				enqueue(&node->open_list, in);
			}
		}
	}
}

t_node	*astar_find(t_mlx *mlx, t_sprite_node *node)
{
	t_node		*parent;
	t_position	tmp;

	while (1)
	{
		parent = dequeue(&node->open_list);
		if (parent == NULL)
			return (NULL);
		push(&node->close_list, parent);
		if (parent->position.x == (int)mlx->user.x
			&& parent->position.y == (int)mlx->user.y)
			return (parent);
		tmp.x = parent->position.x - 1;
		tmp.y = parent->position.y;
		astar_input(mlx, node, parent, &tmp);
		tmp.x = parent->position.x + 1;
		tmp.y = parent->position.y;
		astar_input(mlx, node, parent, &tmp);
		tmp.x = parent->position.x;
		tmp.y = parent->position.y - 1;
		astar_input(mlx, node, parent, &tmp);
		tmp.x = parent->position.x;
		tmp.y = parent->position.y + 1;
		astar_input(mlx, node, parent, &tmp);
	}
}
