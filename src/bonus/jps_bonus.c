/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:41:54 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/03 17:08:10 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		get_manhattan_distance(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

void	direction(t_coord *coord)
{
	coord[0] = (t_coord){0, -1};
	coord[1] = (t_coord){1, 0};
	coord[2] = (t_coord){0, -1};
	coord[3] = (t_coord){-1, 0};
}

t_node	*init_t_node(t_position position, float f_cost, float g_cost, int direction)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->position = position;
	node->f_cost = f_cost;
	node->g_cost = g_cost;
	node->direction = direction;
	node->next = NULL;
	return (node);
}

//int	check_halt_condition(int x, int y, t_map *map)
//{
//	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
//		return (true);
//	if (map->map[y][x] == '1')
//		return (true);
//	return (false);
//}

//int	jps_search(t_sprite_node *node, t_mlx *mlx)
//{
//	t_node	*tmp;
//	t_node	*tmp2;
//	t_map	*map;
//	float	f_cost;
//	float	g_cost;
//	int		i;
//	int		x;
//	int		y;

//	i = 0;
//	map = &mlx->map;
//	while (1)
//	{
//		tmp = dequeue(&node->open_list);
//		if (tmp == NULL)
//			ft_exit("open_list is empty\n");
//		push(&node->close_list, tmp);
//		//printf("tmp->x : %d, tmp->y : %d, tmp->f_cost : %f, tmp->direction : %d, open_list->size : %d user->x : %f, user->y : %f\n", tmp->position.x, tmp->position.y, tmp->f_cost, tmp->direction, node->open_list.size, mlx->user.x, mlx->user.y);
//		x = tmp->position.x;
//		y = tmp->position.y;
//		if (check_halt_condition(x, y, map) == true)
//			continue ;
//		if (x == (int)mlx->user.x && y == (int)mlx->user.y)
//		{
//			tmp = init_t_node((t_position){x, y}, 0, 0, 0);
//			push(&node->close_list, tmp);
//			return (true);
//		}
//		if (tmp->direction & LEFT)
//		{
//			while (1)
//			{
//				//check halt
//				x += -1;
//				if (check_halt_condition(x, y, map) == true)
//					continue ;
//				if (x == (int)mlx->user.x && y == (int)mlx->user.y)
//				{
//					tmp = init_t_node((t_position){x, y}, 0, 0, 0);
//					push(&node->close_list, tmp);
//					return (true);
//				}
//				//check up and down forced neighbor
//				if (y - 1 > 0 && x - 1 > 0 && map->map[y - 1][x] == '1' && map->map[y - 1][x - 1] != '1') //maybe occur error in door
//				{
//					//add forced neighbor
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, (int)mlx->user.x, (int)mlx->user.y));
//					tmp = init_t_node((t_position){x, y - 1}, g_cost, f_cost, UP | LEFT);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//				if (y + 1 < map->h && x - 1 > 0 && map->map[y + 1][x] == '1' && map->map[y + 1][x - 1] != '1')
//				{
//					//add forced neighbor
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, (int)mlx->user.x, (int)mlx->user.y));
//					tmp = init_t_node((t_position){x, y + 1}, f_cost, g_cost, DOWN | LEFT);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//			}
//		}
//		x = tmp->position.x;
//		y = tmp->position.y;
//		if (tmp->direction & RIGHT)
//		{
//			while (1)
//			{
//				//check right
//				x += 1;
//				if (check_halt_condition(x, y, map) == true)
//					continue ;
//				if (x == (int)mlx->user.x && y == (int)mlx->user.y)
//				{
//					tmp = init_t_node((t_position){x, y}, 0, 0, 0);
//					push(&node->close_list, tmp);
//					return (true);
//				}
//				//check up and down forced neighbor
//				if (y - 1 > 0 && x + 1 < map->w && map->map[y - 1][x] == '1' && map->map[y - 1][x + 1] != '1') //maybe occur error in door
//				{
//					//add forced neighbor
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, (int)mlx->user.x, (int)mlx->user.y));
//					tmp = init_t_node((t_position){x, y - 1}, f_cost, g_cost, UP | RIGHT);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//				if (y + 1 < map->h && x + 1 < map->w && map->map[y + 1][x] == '1' && map->map[y + 1][x + 1] != '1')
//				{
//					//add forced neighbor
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, (int)mlx->user.x, (int)mlx->user.y));
//					tmp = init_t_node((t_position){x, y + 1}, f_cost, g_cost, DOWN | RIGHT);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//			}
//		}
//		x = tmp->position.x;
//		y = tmp->position.y;
//		if (tmp->direction & UP)
//		{
//			while (1)
//			{
//				//check up
//				y += -1;
//				if (check_halt_condition(x, y, map) == true)
//					continue ;
//				if (x == (int)mlx->user.x && y == (int)mlx->user.y)
//				{
//					tmp = init_t_node((t_position){x, y}, 0, 0, 0);
//					push(&node->close_list, tmp);
//					return (true);
//				}
//				//check left and right forced neighbor
//				if (x - 1 > 0 && y - 1 > 0 && map->map[y][x - 1] == '1' && map->map[y - 1][x - 1] != '1') 
//				{
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, (int)mlx->user.x, (int)mlx->user.y));
//					tmp = init_t_node((t_position){x - 1, y}, f_cost, g_cost, LEFT | UP);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//				if (x + 1 < map->w && y - 1 > 0 && map->map[y][x + 1] == '1' && map->map[y - 1][x + 1] != '1')
//				{
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, (int)mlx->user.x, (int)mlx->user.y));
//					tmp = init_t_node((t_position){x + 1, y}, f_cost, g_cost, RIGHT | UP);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//			}
//		}
//		x = tmp->position.x;
//		y = tmp->position.y;
//		if (tmp->direction & DOWN)
//		{
//			while (1)
//			{
//				//check down
//				y += 1;
//				if (check_halt_condition(x, y, map) == true)
//					continue ;
//				if (x == (int)mlx->user.x && y == (int)mlx->user.y)
//				{
//					tmp = init_t_node((t_position){x, y}, 0, 0, 0);
//					push(&node->close_list, tmp);
//					return (true);
//				}
//				//check left and right forced neighbor
//				if (x - 1 > 0 && y + 1 < map->h && map->map[y][x - 1] == '1' && map->map[y + 1][x - 1] != '1') 
//				{
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, mlx->user.x, mlx->user.y));
//					tmp = init_t_node((t_position){x - 1, y}, f_cost, g_cost, LEFT | DOWN);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//				if (x + 1 < map->w && y + 1 < map->h && map->map[y][x + 1] == '1' && map->map[y + 1][x + 1] != '1')
//				{
//					g_cost = tmp->g_cost + distance(tmp->position.x, tmp->position.y, x, y);
//					f_cost = -(g_cost + get_manhattan_distance(x, y, mlx->user.x, mlx->user.y));
//					tmp = init_t_node((t_position){x + 1, y}, f_cost, g_cost, RIGHT | DOWN);
//					enqueue(&node->open_list, tmp);
//					break ;
//				}
//			}
//		}
//		x = tmp->position.x;
//		y = tmp->position.y;
//		if (tmp->direction & LEFT && tmp->direction & UP && x - 1 > 0 && y - 1 > 0)
//		{
//			g_cost = tmp->g_cost + 1.414;
//			f_cost = -(g_cost + get_manhattan_distance(x, y, mlx->user.x, mlx->user.y));
//			tmp2 = init_t_node((t_position){x - 1, y - 1}, f_cost, g_cost, LEFT | UP);
//			enqueue(&node->open_list, tmp2);
//		}
//		if (tmp->direction & LEFT && tmp->direction & DOWN && x - 1 > 0 && y + 1 < map->h)
//		{
//			g_cost = tmp->g_cost + 1.414;
//			f_cost = -(g_cost + get_manhattan_distance(x, y, mlx->user.x, mlx->user.y));
//			tmp2 = init_t_node((t_position){x - 1, y + 1}, f_cost, g_cost, LEFT | DOWN);
//			enqueue(&node->open_list, tmp2);
//		}
//		if (tmp->direction & RIGHT && tmp->direction & UP && x + 1 < map->w && y - 1 > 0)
//		{
//			g_cost = tmp->g_cost + 1.414;
//			f_cost = -(g_cost + get_manhattan_distance(x, y, mlx->user.x, mlx->user.y));
//			tmp2 = init_t_node((t_position){x + 1, y - 1}, f_cost, g_cost, RIGHT | UP);
//			enqueue(&node->open_list, tmp2);
//		}
//		if (tmp->direction & RIGHT && tmp->direction & DOWN && x + 1 < map->w && y + 1 < map->h)
//		{
//			g_cost = tmp->g_cost + 1.414;
//			f_cost = -(g_cost + get_manhattan_distance(x, y, mlx->user.x, mlx->user.y));
//			tmp2 = init_t_node((t_position){x + 1, y + 1}, f_cost, g_cost, RIGHT | DOWN);
//			enqueue(&node->open_list, tmp2);
//		}
//		if (node->open_list.size == 0)
//			break ;
//	}
//	return (false);
//}

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

t_node	*jps_search_line(t_node *parent, t_sprite_node *node, t_mlx *mlx, t_position *origin)
{
	static t_position	shift[] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; //left, up, right, down
	static t_position	test[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; //pick odd or even
	t_position			position;
	int					dir;
	int					i;
	int					j;
	int					h_cost;
	int					g_cost;

	i = 0;
	dir = parent->direction;
	//push(&node->close_list, parent);
	while (i++ < 4)
	{
		memcpy(&position, origin, sizeof(t_position));
		if ((dir << i) & 1)
		{
			//check end condition
			if (parent->position.x == (int)mlx->user.x 
				&& parent->position.y == (int)mlx->user.y)
				return (parent);
			//check halt condition
			position.x += shift[i - 1].x;
			position.y += shift[i - 1].y;
			if (parent->position.x < 0 || parent->position.y < 0
				|| parent->position.x >= mlx->map.w || parent->position.y >= mlx->map.h
				|| mlx->map.map[parent->position.y][parent->position.x] == '1')
				return (NULL);
			//check forced neighbor, check up and down or left and right using % 2
			j = 0;
			while (j++ < 4)
			{
				if (i % 2 == j % 2)
				{
					if (mlx->map.map[position.y + test[j - 1].y][position.x + test[j - 1].x] == '1' &&
					mlx->map.map[position.y + test[j - 1].y + shift[i - 1].y][position.x + test[j - 1].x + shift[i - 1].x] != '1')
					{
						//add forced neighbor
						h_cost = get_manhattan_distance(position.x, position.y, (int)mlx->user.x, (int)mlx->user.y);
						g_cost = get_manhattan_distance(parent->position.x, parent->position.y, position.x, position.y) + parent->g_cost;
						parent = init_t_node(position, g_cost + h_cost, g_cost, (int)pow(2, i) | (int)pow(2, j));
						enqueue(&node->open_list, parent);
						break ;
					}
				}
			}
			//recursive
			return (jps_search_line(parent, node, mlx, &position));
		}
	}
	return (NULL);
}

t_node	*jps_init_start(t_sprite_node *start, t_mlx *mlx)
{
	static t_position	diagonal[] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}; //left, up, right, down
	t_node	*n;
	t_node	*ret;
	int		i;

	n = (t_node *)malloc(sizeof(t_node));
	n->position.x = (int)start->x;
	n->position.y = (int)start->y;
	n->f_cost = -get_manhattan_distance((int)start->x, (int)start->y, (int)mlx->user.x, (int)mlx->user.y);
	n->g_cost = 0;
	n->direction = LEFT | UP | RIGHT | DOWN;
	n->next = NULL;
	enqueue(&start->open_list, n);
	i = 0;
	while (true)
	{
		n = dequeue(&start->open_list);
		if (n == NULL)
			ft_exit("Monster is not reached\n");
		push(&start->close_list, n);
		ret = jps_search_line(n, start, mlx, &n->position);
		if (ret != NULL)
			return (ret);
		else
		{
			i = 0;
			while (i < 4)
			{
				n = (t_node *)malloc(sizeof(t_node));
				n->position.x = start->x + diagonal[i].x;
				n->position.y = start->y + diagonal[i].y;
				n->f_cost = -get_manhattan_distance((int)n->position.x, (int)n->position.y, (int)mlx->user.x, (int)mlx->user.y);
				n->g_cost = 0;
				n->direction = (int)pow(2, i) | (int)pow(2, (i + 1) % 4);
				n->next = NULL;
				enqueue(&start->open_list, n);
				i++;
			}
		}
		if (start->open_list.size == 0)
			break ;
	}
	return (NULL);
}

void	jps_update_position(t_node *dst, t_sprite_node *start, t_mlx *mlx)
{
	float	dis;
	t_node	*next;

	next = dst->next;
	while (true) //maybe occur error
	{
		if (dst->position.x == start->x && dst->position.y == start->y)
			break ;
		if (!next)
		{
			dst = next;
			next = dst->next;
		}
	}
	dis = distance(start->x, start->y, dst->position.x + 0.5, dst->position.y + 0.5); 
	if ((int)start->x != dst->position.x)
		start->x += (SPRITE_MOVE_SPEED * dis) / (dst->position.x + 0.5 - start->x);
	if ((int)start->y != dst->position.y)
		start->y += (SPRITE_MOVE_SPEED * dis) / (dst->position.y + 0.5 - start->y); //error occur
	printf("node->close_list->x : %d, node->close_list->y : %d\n", dst->position.x, dst->position.y);
	printf("node->x : %f, node->y : %f, user->x : %f, user->y : %f, dis : %f\n", start->x, start->y, mlx->user.x, mlx->user.y, dis);
	sanitize_p_queue(&start->open_list);
	sanitize_p_queue(&start->close_list);
}

void	jps(t_mlx *mlx)
{
	t_sprite_vec	*vec;
	t_sprite_node	*node;
	t_node			*dst;
	int				i;

	vec = &(mlx->sprite_vec);
	i = 0;
	while (i < vec->size)
	{
		node = vec->list[i];
		dst = jps_init_start(node, mlx);
		if (dst != NULL)
			jps_update_position(dst, node, mlx);
		printf("node->close_list->x : %d, node->close_list->y : %d\n", node->close_list.arr[0]->position.x, node->close_list.arr[0]->position.y);
		sanitize_p_queue(&node->open_list);
		sanitize_p_queue(&node->close_list);
		i++;
	}
}

//refine this function

//t_node	*check_neighborhood(t_node *start_node, t_user *user, int dir, t_map *map)
//{
//	t_coord	coord[4];
//	t_node	*node;
//	int		x;
//	int		y;
//	int		i;
//	int		j;

//	direction(coord);
//	i = 0;
//	while (dir)
//	{
//		dir = dir >> 1;
//		x = start_node->coord.x;
//		y = start_node->coord.y;
//		if (dir & 1)
//		{
//			while (1)
//			{
//				x += coord[i].x;
//				y += coord[i].y;
//				if (x < 0 || y < 0 || x >= map->w || y >= map->h)
//					break ;
//				if (map->map[y][x] == '1')
//					break ;
//				j = -1; //check left / right / up / down
//				while (++j < 4)
//				{
//					if (y == (int)user->y && x == (int)user->x)
//						return (start_node);
//					if (i % 2 == j % 2)
//						continue;
//					if (map->map[y + (int)(coord[j].y)][x + (int)(coord[j].x)] == '1')
//					{
//						node = (t_node *)malloc(sizeof(t_node));
//						node->coord.x = x + (int)coord[j].x + (int)coord[i].x;
//						node->coord.y = y + (int)coord[j].y + (int)coord[j].y;
//						node->g_cost = start_node->g_cost + distance(x, y, node->coord.x, node->coord.y);
//						node->f_cost = -(node->g_cost + distance(x, y, user->x, user->y));
//						node->direction = (int)pow(2, j) & (int)pow(2, i);
//						node->next = 0;
//						return (node);
//					}
//				}
//			}
//		}
//		i++;
//	}
//	return (NULL);
//}

//void	jps_search(t_sprite_node *node, t_mlx *mlx)
//{
//	t_node	*tmp;
//	t_node	*tmp2;
//	t_node	*tmp3;
//	t_map	*map;
//	int		i;
//	t_coord	coord[4];

//	map = &(mlx->map);
//	direction(coord);
//	while (1)
//	{
//		tmp = dequeue(&node->open_list);
//		printf("tmp->coord.x: %d, tmp->coord.y: %d, tmp->f_cost : %f, tmp->direction:%d\n", tmp->coord.x, tmp->coord.y, tmp->f_cost, tmp->direction);
//		push(&node->close_list, tmp);
//		tmp2 = check_neighborhood(tmp, &(mlx->user), tmp->direction, map);
//		if (tmp == tmp2)
//		{
//			break ;
//		}
//		if (tmp2 == NULL)
//		{
//			i = 0;
//			while (i < 4) //find next diagonal
//			{
//				tmp3 = (t_node *)malloc(sizeof(t_node));
//				tmp3->coord.x = tmp->coord.x + coord[i].x + coord[(i + 1) % 4].x;
//				tmp3->coord.y = tmp->coord.y + coord[i].y + coord[(i + 1) % 4].y;
//				tmp3->g_cost = tmp->g_cost + 1.414;
//				tmp3->f_cost = -(tmp3->g_cost + distance(tmp3->coord.x, tmp3->coord.y, mlx->user.x, mlx->user.y));
//				tmp3->direction = (int)pow(2, i) | (int)pow(2, (i + 1) % 4);
//				tmp3->next = NULL;
//				push(&node->open_list, tmp3);
//				i += 1;
//			}
//		}
//		else
//			push(&node->open_list, tmp);
//		if (node->open_list.size == 0)
//			break ;
//	}
//}

//void	update_node(t_sprite_node *node)
//{
//	float	diagonal;
//	float	moving_scale;
//	float	diff_x;
//	float	diff_y;

//	diff_x = node->x - node->next_node->coord.x;
//	diff_y = node->y - node->next_node->coord.y;
//	diagonal = sqrt(diff_x * diff_x + diff_y * diff_y);
//	moving_scale = SPRITE_MOVE_SPEED / diagonal;
//	node->x += (moving_scale * diff_x);
//	node->y += (moving_scale * diff_y);
//}

///**
// * @brief Jump Point Search
// * while sprite_vec is not empty
// * 
//*/
//void	jps(t_mlx *mlx)
//{
//	t_sprite_vec	*vec;
//	t_sprite_node	*node;
//	t_node			*n;
//	int				i;

//	vec = &(mlx->sprite_vec);
//	i = 0;
//	while (i < vec->size)
//	{
//		n = (t_node *)malloc(sizeof(t_node));
//		node = vec->list[i];
//		n->coord.x = node->x;
//		n->coord.y = node->y;
//		n->f_cost = -distance(node->x, node->y, mlx->user.x, mlx->user.y);
//		n->g_cost = 0;
//		n->direction = LEFT | UP | RIGHT | DOWN;
//		n->next = NULL;
//		enqueue(&node->open_list, n);
//		jps_search(node, mlx);
//		update_node(node);
//		i++;
//	}
//}
