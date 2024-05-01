/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:41:54 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/01 18:33:28 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	direction(t_coord *coord)
{
	coord[0] = (t_coord){0, -1};
	coord[1] = (t_coord){1, 0};
	coord[2] = (t_coord){0, -1};
	coord[3] = (t_coord){-1, 0};
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

void	

void	jps(t_mlx *mlx)
{
	t_sprite_vec	*vec;
	t_sprite_node	*node;
	t_node			*n;
	int				i;

	vec = &(mlx->sprite_vec);
	i = 0;
	while (i < vec->size)
	{
		n = (t_node *)malloc(sizeof(t_node));
		node = vec->list[i];
		n->coord.x = node->x;
		n->coord.y = node->y;
		n->f_cost = -distance(node->x, node->y, mlx->user.x, mlx->user.y);
		n->g_cost = 0;
		n->direction = LEFT | UP | RIGHT | DOWN;
		n->next = NULL;
		enqueue(&node->open_list, n);
		jps_search(node, mlx);
		update_node(node);
		i++;
	}
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
