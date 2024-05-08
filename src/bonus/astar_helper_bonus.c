/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:35:01 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/08 13:25:18 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_manhattan_distance(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

t_node	*init_node(t_node *start,
	t_position *target, t_coord *user, int direction)
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

static void	update_position_helper(t_node *dst, t_sprite_node *start)
{
	float	dis;
	t_coord	tmp;

	dis = distance(start->x, start->y,
			dst->position.x + 0.5, dst->position.y + 0.5);
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

void	update_position(t_node *dst, t_sprite_node *start)
{
	t_node	*next;

	next = dst->next;
	while (true)
	{
		if (dst->position.x == (int)start->x
			&& dst->position.y == (int)start->y)
			return ;
		if (next)
		{
			if (next->position.x == (int)start->x
				&& next->position.y == (int)start->y)
				break ;
			dst = next;
			next = dst->next;
		}
		else
			break ;
	}
	update_position_helper(dst, start);
}
