/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:50:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 20:29:44 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	map_cub_lst_2(char *line, int *flag)
{
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	if (tmp[0] == '\0' && *flag == false)
	{
		*flag = true;
		free(tmp);
		free(line);
		return (SUCCESS);
	}
	if (tmp[0] != '\0' && *flag == true)
		ft_exit("Invalid map in enter");
	free(tmp);
	return (FAIL);
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
		ft_sanitize_enter(line);
		if (map_cub_lst_2(line, &flag) == SUCCESS)
			continue ;
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
		ft_exit("Malloc failed");
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
	map_cub_lst_to_arr(head, map);
	free_lst(head);
	return (SUCCESS);
}
