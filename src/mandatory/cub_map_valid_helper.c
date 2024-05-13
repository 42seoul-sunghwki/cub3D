/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_valid_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:18:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/13 15:18:40 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	push_init_node(t_map *map, t_position posit,
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
