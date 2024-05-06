/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:23:18 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 18:42:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d_bonus.h"

char	get_map(int x, int y, int h, char **map)
{
	//printf("x : %d, y : %d, h : %d, h - y - 1 : %d, map: [%c]\n", x, y, h, h-y-1, map[h-y-1][x]);
	(void) h;
	return (map[y][x]);
}

int		get_manhattan_distance(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

t_node	*init_node(t_node *start, t_position *target, t_coord *user, int direction)
{ 
	t_node		*node;
	t_position	int_user;

	node = (t_node *)malloc(sizeof(t_node));
	int_user.x = user->x;
	int_user.y = user->y;
	node->position = *target;
	node->g_cost = start->g_cost + get_manhattan_distance(start->position.x,
			start->position.y, target->x, target->y);
	node->f_cost = -(node->g_cost + get_manhattan_distance(target->x,
			target->y, int_user.x, int_user.y));
	node->next = NULL;
	node->direction = direction;
	node->dir.x = 0;
	node->dir.y = 0;
	return (node);
}

int	check_halt_condition(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->w 
		|| y >= map->h || get_map(x, y, map->h, map->map) == '1')
	{
		printf("halt_condition\n");
		return (true);
	}
	return (false);
}

void	sanitize_p_queue(t_p_queue *queue)
{
	int		i;
	t_node	**arr;

	arr = queue->arr;
	i = 1;
	while (i <= queue->size)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	queue->size = 0;
}

int		check_map_range(t_map *map, t_position *position)
{
	if (position->x < 0 || position->y < 0
		|| position->x >= map->w || position->y >= map->h)
	{
		printf("out of map range\n");
		return (true);
	}
	//printf("check_map_range x : %d, y : %d, map : [%c]\n", position->x, position->y, get_map(position->x, position->y, map->h, map->map));
	return (false);
}

void	update_position(t_node *dst, t_sprite_node *start, t_mlx *mlx)
{
	float	dis;
	t_node	*next;
	t_coord	tmp;

	next = dst->next;
	(void)mlx;
	while (true)
	{
		if (dst->position.x == (int)start->x && dst->position.y == (int)start->y)
		{
			printf("find user\n");
			return ;
		}
		if (next)
		{
			if (next->position.x == (int)start->x && next->position.y == (int)start->y)
				break ;
			dst = next;
			next = dst->next;
		}
		else
			break ;
	}
	dis = distance(start->x, start->y, dst->position.x + 0.5, dst->position.y + 0.5);
	tmp.x = dst->position.x + 0.5 - start->x;
	tmp.y = dst->position.y + 0.5 - start->y;
	if ((int)start->x != dst->position.x)
	{
		if (start->sprite_type == DANCING_BEAR)
			start->x += (BEAR_MOVE_SPEED * dis) / tmp.x;
		else if (start->sprite_type == DANCING_CAT)
			start->x += (CAT_MOVE_SPEED * dis) / tmp.x;
		else if (start->sprite_type == DANCING_DOG)
			start->x += (DOG_MOVE_SPEED * dis) / tmp.x;
	}
	if ((int)start->y != dst->position.y)
	{
		if (start->sprite_type == DANCING_BEAR)
			start->y += (BEAR_MOVE_SPEED * dis) / tmp.y;
		else if (start->sprite_type == DANCING_CAT)
			start->y += (CAT_MOVE_SPEED * dis) / tmp.y;
		else if (start->sprite_type == DANCING_DOG)
			start->y += (DOG_MOVE_SPEED * dis) / tmp.y;
	}
}

int		find_target(t_p_queue *list, t_position *position)
{
	int	i;

	i = 0;
	while (++i < list->size)
	{
		//printf("find_target x : %d, y : %d, f_cost : %f\n", list->arr[i]->position.x, list->arr[i]->position.y, list->arr[i]->f_cost);
		if (list->arr[i]->position.x == position->x
			&& list->arr[i]->position.y == position->y)
		{
			return (i);
		}
	}
	return (0);
}

void	delete_p_queue(t_p_queue *list, int i)
{
	t_node	*deleted;

	deleted = list->arr[i];
	list->arr[i] = list->arr[list->size];
	list->size--;
	max_heapify(list, i);
	increase_value(list, i, list->arr[i]);
}

void	astar_input(t_mlx *mlx, t_sprite_node *node, t_node *parent, t_position *tmp)
{
	t_coord	user;
	t_node	*in;

	user.x = mlx->user.x;
	user.y = mlx->user.y;
	if (check_halt_condition(tmp->x, tmp->y, &mlx->map) == false)
	{
		if (find_target(&node->close_list, tmp) == 0)
		{
			in = init_node(parent, tmp, &user, 5);
			in->next = parent;
			//printf("open_list node\n");
			//i = find_target(&node->open_list, tmp);
			//if (i != 0)
			//{
			//	if (in->f_cost < node->open_list.arr[i]->f_cost)
			//	{
			//		delete_p_queue(&node->open_list, i);
			//		enqueue(&node->open_list, in);
			//	}
			//	else
			//		free(in);
			//}
			//else
				enqueue(&node->open_list, in);
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
		if (parent->position.x == (int)mlx->user.x
			&& parent->position.y == (int)mlx->user.y)
			return (parent);
		push(&node->close_list, parent);
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

void	astar_init(t_sprite_node *node, t_mlx *mlx)
{
	t_node	*ret;
	t_node	start;
	t_coord	user;

	user.x = mlx->user.x;
	user.y = mlx->user.y;
	start.g_cost = 0;
	start.position.x = (int)node->x;
	start.position.y = (int)node->y;
	ret = init_node(&start, &start.position, &user, 5);
	enqueue(&node->open_list, ret);
}

void	astar(t_mlx *mlx)
{
	t_sprite_vec	*vec;
	t_sprite_node	*node;
	t_node			*dst;
	int				i;

	vec = &mlx->sprite_vec;
	i = 0;
	while (i < vec->size)
	{
		node = vec->list[i];
		astar_init(node, mlx);
		dst = astar_find(mlx, node);
		if (dst != NULL)
			update_position(dst, node, mlx);
		else
			printf("dst is NULL\n");
		sanitize_p_queue(&node->open_list);
		sanitize_p_queue(&node->close_list);
		i++;
	}
}
