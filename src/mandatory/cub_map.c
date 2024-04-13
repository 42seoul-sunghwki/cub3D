/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:50:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/13 16:54:54 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_cub_lst_2(char *line, int *flag)
{
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	if (*flag == true && tmp[0] == '\0')
	{
		printf("Error\nInvalid map in map_cub_lst\n");
		exit (1);
	}
	free(tmp);
}

char	*map_cub_lst(int fd, t_lst_head *head)
{
	char		*line;
	int			flag;
	t_line_lst	*new;

	flag = false;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			flag = true;
			continue ;
		}
		ft_sanitize_enter(line);
		map_cub_lst_2(line, &flag);
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
		printf("Error\nInvalid map in map_cub_lst_to_arr\n");
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
		exit (1);
	free_lst(head);
	return (SUCCESS);
}
