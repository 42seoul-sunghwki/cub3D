/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_thread_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:49:41 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/07 22:15:18 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		update_position(dst, node);
	else
		printf("dst is NULL\n");
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
	printf("%s\n", __func__);
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
