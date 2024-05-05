/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:41:54 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/05 22:38:18 by sunghwki         ###   ########.fr       */
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
	node->f_cost = node->g_cost + get_manhattan_distance(target->x,
			target->y, int_user.x, int_user.y);
	node->next = NULL;
	node->direction = direction;
	node->dir.x = 0;
	node->dir.y = 0;
	return (node);
}

int	check_halt_condition(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (true);
	if (map->map[y][x] == '1')
		return (true);
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
		|| position->x >= map->w || position->y >= map->h
		|| map->map[position->y][position->x] == '1')
		return (true);
	return (false);
}

/**
 * jps_find_line - find user in line and find forced neighbor
*/
t_node	*jps_find_line(t_node *start, t_sprite_node *sprite, t_mlx *mlx, t_position *origin)
{
	t_position	check_position;
	t_position	forced_position;
	t_node		*ret;
	float		f_cost;
	float		g_cost;

	check_position.x = origin->x;
	check_position.y = origin->y;
	while (1)
	{
		//printf("check_position.x : %d, check_position.y : %d start->dir.x : %d, start->dir.y : %d\n", check_position.x, check_position.y, start->dir.x, start->dir.y);
		if (check_halt_condition(check_position.x, check_position.y, &mlx->map) == true)
			return (NULL);
		if (check_position.x == (int)mlx->user.x && check_position.y == (int)mlx->user.y)
		{
			ret = init_t_node(check_position, 0, 0, 0);
			ret->next = start;
			push(&sprite->close_list, ret);
			return (ret);
		}
		//find forced neighbor
		if (start->dir.x == 0) //go up or down,  check left or right
		{
			forced_position.x = check_position.x + 1; //check right
			forced_position.y = check_position.y;
			if (check_map_range(&mlx->map, &forced_position) == false
				&& check_map_range(&mlx->map, &(t_position){forced_position.x + start->dir.x, forced_position.y + start->dir.y}) == false)
			{
				if (mlx->map.map[forced_position.y][forced_position.x] == '1'
					&& mlx->map.map[forced_position.y + start->dir.y][forced_position.x + start->dir.x] != '1')
				{
					g_cost = get_manhattan_distance(start->position.x, start->position.y, check_position.x, check_position.y) + start->g_cost;
					f_cost = get_manhattan_distance(check_position.x, check_position.y, (int)mlx->user.x, (int)mlx->user.y) + g_cost;
					if (start->dir.y == -1) //up / right forced
						ret = init_t_node(forced_position, -f_cost, g_cost, 1);
					else // down / right forced
						ret = init_t_node(forced_position, -f_cost, g_cost, 3);
					ret->next = start;
					enqueue(&sprite->open_list, ret);
				}
			}
			forced_position.x = check_position.x - 1; //check left
			forced_position.y = check_position.y;
			if (check_map_range(&mlx->map, &forced_position) == false
				&& check_map_range(&mlx->map, &(t_position){forced_position.x + start->dir.x, forced_position.y + start->dir.y}) == false)
			{
				if (mlx->map.map[forced_position.y][forced_position.x] == '1'
					&& mlx->map.map[forced_position.y + start->dir.y][forced_position.x + start->dir.x] != '1')
				{
					g_cost = get_manhattan_distance(start->position.x, start->position.y, check_position.x, check_position.y) + start->g_cost;
					f_cost = get_manhattan_distance(check_position.x, check_position.y, (int)mlx->user.x, (int)mlx->user.y) + g_cost;
					if (start->dir.y == -1) //up / left forced
						ret = init_t_node(forced_position, -f_cost, g_cost, 0);
					else //down / left forced
						ret = init_t_node(forced_position, -f_cost, g_cost, 2);
					ret->next = start;
					enqueue(&sprite->open_list, ret);
				}
			}
		}
		else if (start->dir.y == 0) //go left and right
		{
			forced_position.x = check_position.x;
			forced_position.y = check_position.y + 1;
			if (check_map_range(&mlx->map, &forced_position) == false //go down
				&& check_map_range(&mlx->map, &(t_position){forced_position.x + start->dir.x, forced_position.y + start->dir.y}) == false)
			{
				if (mlx->map.map[forced_position.y][forced_position.x] == '1'
					&& mlx->map.map[forced_position.y + start->dir.y][forced_position.x + start->dir.x] != '1')
				{
					g_cost = get_manhattan_distance(start->position.x, start->position.y, check_position.x, check_position.y) + start->g_cost;
					f_cost = get_manhattan_distance(check_position.x, check_position.y, (int)mlx->user.x, (int)mlx->user.y) + g_cost;
					if (start->dir.x == -1) // down / left
						ret = init_t_node(forced_position, -f_cost, g_cost, 2);
					else //down / right
						ret = init_t_node(forced_position, -f_cost, g_cost, 3);
					ret->next = start;
					enqueue(&sprite->open_list, ret);
				}
			}
			forced_position.x = check_position.x;
			forced_position.y = check_position.y - 1;
			if (check_map_range(&mlx->map, &forced_position) == false
				&& check_map_range(&mlx->map, &(t_position){forced_position.x + start->dir.x, forced_position.y + start->dir.y}) == false)
			{
				if (mlx->map.map[forced_position.y][forced_position.x] == '1'
					&& mlx->map.map[forced_position.y + start->dir.y][forced_position.x + start->dir.x] != '1')
				{
					g_cost = get_manhattan_distance(start->position.x, start->position.y, check_position.x, check_position.y) + start->g_cost;
					f_cost = get_manhattan_distance(check_position.x, check_position.y, (int)mlx->user.x, (int)mlx->user.y) + g_cost;
					if (start->dir.x == -1) //up , left
					ret = init_t_node(forced_position, -f_cost, g_cost, 0);
					else //up / right
						ret = init_t_node(forced_position, -f_cost, g_cost, 1);
					ret->next = start;
					enqueue(&sprite->open_list, ret);
				}
			}
		}
		check_position.x += start->dir.x;
		check_position.y += start->dir.y;
	}
	return (NULL);
}

t_node	*jps_find_diagonal(t_node *start, t_sprite_node *sprite, t_mlx *mlx, t_position *origin)
{
	static t_position	shift[] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
	t_position			check_position;
	t_node				*node;
	char				**map;

	//check diagonal foreign
	//check RIGHT_UP / LEFT_DOWN 1, 2
	map = mlx->map.map;
	if (start->direction == LEFT_UP || start->direction == RIGHT_DOWN)
	{
		//RIGHT_UP 1
		check_position.x = origin->x + shift[RIGHT_UP].x;
		check_position.y = origin->y + shift[RIGHT_UP].y; //check right == '1' and right_up == '0'
		if (map[origin->y][origin->x + shift[RIGHT_UP].x] == '1' 
			&& map[check_position.y][check_position.x] == '0') //
		{
			node = init_node(start, &check_position, (t_coord *){(int)mlx->user.x, (int)mlx->user.y}, start->direction);
			enqueue(&sprite->open_list, node);
			return (NULL);
		}		
		check_position.x = origin->x + shift[LEFT_DOWN].x;
		check_position.y = origin->y + shift[LEFT_DOWN].y;
		if (map[origin->y][origin->x + shift[LEFT_DOWN].x] == '1'
		&& map[check_position.y][check_position.x] == '0')
		{
			node = init_node(start, &check_position, (t_coord *){(int)mlx->user.x, (int)mlx->user.y}, start->direction);
			enqueue(&sprite->open_list, node);
			return (NULL);
		}
	} //check RIGHT_DOWN / LEFT_UP 0, 3
	else if (start->direction == RIGHT_UP || start->direction == LEFT_DOWN) 
	{
		check_position.x = origin->x + shift[RIGHT_DOWN].x;
		check_position.y = origin->y + shift[RIGHT_DOWN].y;
		if (map[origin->y][origin->x + shift[RIGHT_DOWN].x] == '1'
		&& map[check_position.y][check_position.x] == '0')
		{
			node = init_node(start, &check_position, (t_coord *){(int)mlx->user.x, (int)mlx->user.y}, start->direction);
			enqueue(&sprite->open_list, node);
			return (NULL);
		}
		check_position.x = origin->x + shift[LEFT_UP].x;
		check_position.y = origin->y + shift[LEFT_UP].y;
		if (map[origin->y][origin->x + shift[LEFT_UP].x] == '1'
		&& map[check_position.y][check_position.x] == '0')
		{
			node = init_node(start, &check_position, (t_coord *){(int)mlx->user.x, (int)mlx->user.y}, start->direction);
			enqueue(&sprite->open_list, node);
			return (NULL);
		}
	}
}

t_node	*jps_find_diagonal_sub(t_node *start, t_sprite_node *sprite, t_mlx *mlx, t_position *origin)
{
	
}

/**
 * jps_find - start jps_find_line and shift position to find user
*/
t_node	*jps_find(t_node *start, t_sprite_node *sprite, t_mlx *mlx, t_position *origin)
{
	static t_position	shift[] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
	int					i;
	t_position			next_pos;
	t_node				*ret;

	next_pos.x = origin->x;
	next_pos.y = origin->y;
	i = 0;
	while (1)
	{
		printf("jps_find\n");
		if (check_halt_condition(next_pos.x, next_pos.y, &mlx->map) == true)
			return (NULL);
		start->dir.x = shift[start->direction].x;
		start->dir.y = 0;
		ret = jps_find_line(start, sprite, mlx, &next_pos);
		if (ret != NULL)
			return (ret);
		start->dir.x = 0;
		start->dir.y = shift[start->direction].y;
		ret = jps_find_line(start, sprite, mlx, &next_pos);
		if (ret != NULL)
			return (ret);
		next_pos.x += shift[start->direction].x;
		next_pos.y += shift[start->direction].y;
		i++;
	}
}

/**
 * jps_dequeue - dequeue node from open_list
*/
t_node	*jps_dequeue(t_sprite_node *sprite, t_mlx *mlx)
{
	t_node		*node;
	t_node		*ret;

	while (1)
	{
		printf("jps_dequeue\n");
		node = dequeue(&sprite->open_list);
		if (node == NULL)
			return (NULL);
		ret = jps_find(node, sprite, mlx, &node->position);
		if (ret != NULL)
			return (ret);
	}
}

void	jps_init(t_sprite_node *start, t_mlx *mlx)
{
	t_node	*n[4];
	int		i;

	i = 0;
	while (i < 4)
	{
		n[i] = (t_node *)malloc(sizeof(t_node));
		n[i]->position.x = (int)start->x;
		n[i]->position.y = (int)start->y;
		n[i]->f_cost = -get_manhattan_distance((int)start->x, (int)start->y, (int)mlx->user.x, (int)mlx->user.y);
		n[i]->g_cost = 0;
		n[i]->dir.x = 0;
		n[i]->dir.y = 0;
		n[i]->next = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		n[i]->direction = i;
		enqueue(&start->open_list, n[i]);
		i++;
	}
}

void	jps_update_position(t_node *dst, t_sprite_node *start, t_mlx *mlx)
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
	if (mlx->map.map[(int)start->y][(int)start->x] == '1')
	{
		start->x = round(start->x);
		start->y = round(start->y);
	}
	printf("dst->x : %d, dst->y : %d\n", dst->position.x, dst->position.y);
	printf("node->x : %f, node->y : %f, user->x : %f, user->y : %f, dis : %f\n", start->x, start->y, mlx->user.x, mlx->user.y, dis);
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
		printf("vec size : %d, i : %d\n", vec->size, i);
		node = vec->list[i];
		jps_init(node, mlx);
		dst = jps_dequeue(node, mlx);
		if (dst != NULL)
			jps_update_position(dst, node, mlx);
		else
			printf("dst is NULL\n");
		sanitize_p_queue(&node->open_list);
		sanitize_p_queue(&node->close_list);
		i++;
	}
}

