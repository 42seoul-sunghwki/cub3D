/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:50:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 21:38:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//int	check_map_cub(char **l, int fd, t_map *map, t_user *player)
//{
//	int			i;
//	char		*line;
//	t_lst_head	*head;

//	i = -1;
//	line = *l;
//	while (line[i])
//	{
//		if (line[i] == ' ' && line[i] == '1' && line[i] == '0')
//			continue ;
//		if (line[i] == 'N' && line[i] == 'S' && line[i] == 'W' && line[i] == 'E')
//		{
//			player->x = i;
//			player->y = map->height;
//		}
//		i++;
//	}
//	return (SUCCESS);
//}

char	*map_cub(char **line, int fd, t_map *map, t_user *player)
{
	char		*tmp;
	t_lst_head	*head;
	t_line_lst	*new;

	head = init_lst_head();
	if (!head)
		return (NULL);
	new = init_line_lst(*line);
	if (!new)
		return (NULL);
	head = push_lst(head, new);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		new = init_line_lst(tmp);
		if (!new)
			return (NULL);
		head = push_lst(head, new);
	}
	
}
