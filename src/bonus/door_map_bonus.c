/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:04:03 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/03 23:02:31 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_door	*get_door(t_mlx	*graphic, int y, int x)
{
	int		low;
	int		high;
	int		mid;
	t_door	*cur_door;
	int		index;

	low = 0;
	high = graphic->num_door - 1;
	index = y * graphic->map.w + x;
	while (low <= high)
	{
		mid = (high + low) / 2;
		cur_door = &graphic->door[mid];
		if (cur_door->index == index)
			return (cur_door);
		else if (cur_door->index < index)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (NULL);
}
