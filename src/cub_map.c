/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:50:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 14:42:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*map_cub_lst(int fd, t_lst_head *head)
{
	char		*line;
	t_line_lst	*new;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("line: %s\n", line); //tmp
		line = ft_sanitize_enter(line);
		if (line[0] == '\0')
			break ;
		if (check_map_cub(line) == FAIL)
			return (line);
		new = init_line_lst(line);
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
	{
		perror("Error\nInvalid map");
		return (FAIL);
	}
	map->map = arr;
	return (SUCCESS);
}

int	map_cub(char *line, int fd, t_map *map)
{
	t_lst_head	*head;
	t_line_lst	*new;

	check_map_cub(line);
	head = init_lst_head();
	if (!head)
		return (FAIL);
	new = init_line_lst(line);
	if (!new)
		return (FAIL);
	head = push_lst(head, new);
	map_cub_lst(fd, head);
	if (map_cub_lst_to_arr(head, map) == FAIL)
	{
		perror("Error\nInvalid map");
		exit (1);
	}
	free_lst(head);
	return (SUCCESS);
}
