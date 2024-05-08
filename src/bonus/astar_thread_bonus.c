/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_thread_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:49:41 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/08 16:55:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//static void	update_position_hitbox(t_map *map, t_sprite_node *start)
//{
//	t_coord	tmp;
//	t_position	sprite;
//	//int		i;

//	tmp = (t_coord){start->x, start->y};
//	sprite = (t_position){(int)start->x, (int)start->y};
//	if (map->map[sprite.y - 1][sprite.x] == '1'
//		&& sprite.y - 1 == (int)(start->y - HITBOX))
//		start->y = (int)start->y + HITBOX;

//	if (map->map[sprite.y + 1][sprite.x] == '1'
//		&& sprite.y + 1 == (int)(start->y + 1 + HITBOX))
//		start->y = (int)start->y + 1 - HITBOX;

//	if (map->map[sprite.y][sprite.x - 1] == '1'
//		&& sprite.x - 1 == (int)(start->x - HITBOX))
//		start->x = (int)start->x + HITBOX;
		
//	if (map->map[sprite.y][sprite.x + 1] == '1'
//		&& sprite.x + 1 == (int)(start->x + 1 + HITBOX))
//		start->x = (int)start->x + 1 - HITBOX;
//	//check left
//	//i = -1;
//	//while (i <= 1)
//	//{
//	//	if (map->map[sprite.y - 1][sprite.x + i] == '1'
//	//		&& sprite.y - 1 == (int)(start->y - HITBOX))
//	//	{
//	//		start->y = (int)start->y + HITBOX;
//	//	}
//	//	i++;
//	//}
//	//i = -1;
//	//while (i <= 1)
//	//{
//	//	if (map->map[sprite.y + 1][sprite.x + i] == '1'
//	//		&& sprite.y + 1 == (int)(start->y + HITBOX))
//	//	{
//	//		start->y = (int)start->y - HITBOX;
//	//	}
//	//	i++;
//	//}
//	//i = -1;
//	//while (i <= 1)
//	//{
//	//	if (map->map[sprite.y + i][sprite.x - 1] == '1'
//	//		&& sprite.x - 1 == (int)(start->x - HITBOX))
//	//	{
//	//		start->x = (int)start->x + HITBOX;
//	//	}
//	//	i++;
//	//}
//	//i = -1;
//	//while (i <= 1)
//	//{
//	//	if (map->map[sprite.y + i][sprite.x + 1] == '1'
//	//		&& sprite.x + 1 == (int)(start->x + HITBOX))
//	//	{
//	//		start->x = (int)start->x - HITBOX;
//	//	}
//	//	i++;
//	//}
//}


void	astar_routine(void *in)
{
	t_astar			*astar;
	t_sprite_node	*node;
	t_mlx			*mlx;
	t_node			*dst;

	astar = (t_astar *)in;
	node = astar->node;
	mlx = astar->mlx;
	astar_init(node, mlx);
	dst = astar_find(mlx, node);
	if (dst != NULL)
	{
		update_position(dst, node);
		//update_position_hitbox(&mlx->map, node);
	}
	sanitize_p_queue(&node->open_list);
	sanitize_p_queue(&node->close_list);
}

void	astar_thread(t_mlx *graphic)
{
	t_astar			*astar;
	t_sprite_vec	*vec;
	int				i;

	i = -1;
	vec = &graphic->sprite_vec;
	start_wait_for_threads(&graphic->pool, vec->size);
	while (++i < vec->size)
	{
		astar = (t_astar *)malloc(sizeof(t_astar));
		astar->mlx = graphic;
		astar->node = vec->list[i];
		add_task(&graphic->pool, create_task(astar_routine, astar));
	}
	wait_for_threads(&graphic->pool);
}
