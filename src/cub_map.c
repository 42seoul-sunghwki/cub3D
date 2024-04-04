/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:50:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 19:57:06 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_cub(char *line, t_map *map)
{
	int		i;

	i = -1;
	while (line[i])
	{
		if (line[i] == ' ' && line[i] == '1' && line[i] == '0')
			continue ;
		if (line[i] == 'N' && line[i] == 'S' && line[i] == 'W' && line[i] == 'E')
		{
			map->player.x = i;
			map->player.y = map->map_height;
		}
		i++;
	}
	return (SUCCESS);
}
