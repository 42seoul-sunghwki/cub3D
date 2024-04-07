/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:50:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/05 16:14:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_cub(char *line)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (line[i] != ' ')
		{
			flag = 1;
			continue ;
		}
		if (line[i] == ' ' && flag == 1)
			return (FAIL);
		if (line[i] != '1' && line[i] != '0')
			return (FAIL);
		if (line[i] != 'D' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] == 'E')
			return (FAIL);
	}
	return (SUCCESS);
}

char	*map_cub_lst(int fd, t_lst_head *head)
{
	char		*tmp;
	char		**arr;
	t_line_lst	*new;

	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (check_map_cub(tmp) == FAIL)
			return (tmp);
		new = init_line_lst(tmp);
		head = push_lst(head, new);
	}
	return (NULL);
}

int	map_cub_lst_to_arr(t_lst_head *head, t_map *map)
{
	char	**arr;

	map->w = head->w;
	map->h = head->h;
	arr = lst_to_arr(head);
	if (!arr)
		return (FAIL);
	map->map = arr;
	return (SUCCESS);
}

int	map_cub(char **line, int fd, t_map *map, t_user *player)
{
	char		**arr;
	t_lst_head	*head;
	t_line_lst	*new;

	head = init_lst_head();
	if (!head)
		return (FAIL);
	new = init_line_lst(*line);
	if (!new)
		return (FAIL);
	head = push_lst(head, new);
	*line = map_cub_lst(fd, head);
	if (map_cub_lst_to_arr(head, map) == FAIL)
	{
		free_lst(head);
		return (FAIL);
	}
	return (SUCCESS);
}
