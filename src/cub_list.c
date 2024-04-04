/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:47:42 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/04 21:28:53 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_lst_head	*push_lst(t_lst_head *head, t_line_lst *new)
{
	t_line_lst	*tmp;

	if (!head->head)
	{
		head->head = new;
		head->tail = new;
	}
	else
	{
		tmp = head->tail;
		tmp->next = new;
		head->tail = new;
	}
	head->h++;
	if (new->size > head->w)
		head->w = new->size;
	return (head);
}

char	**lst_to_arr(t_lst_head *head)
{
	char		**arr;
	t_line_lst	*tmp;
	int			i;

	arr = (char **)malloc(sizeof(char *) * (head->h + 1));
	if (!arr)
		return (NULL);
	tmp = head->head;
	i = 0;
	while (tmp)
	{
		arr[i] = tmp->line;
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

t_line_lst	*init_line_lst(char *line)
{
	t_line_lst	*new;

	new = (t_line_lst *)malloc(sizeof(t_line_lst));
	if (!new)
		return (NULL);
	new->line = line;
	new->size = ft_strlen(line);
	new->next = NULL;
	return (new);
}

t_lst_head	*init_lst_head(void)
{
	t_lst_head	*new;

	new = (t_lst_head *)malloc(sizeof(t_lst_head));
	if (!new)
		return (NULL);
	new->head = NULL;
	new->tail = NULL;
	new->w = 0;
	new->h = 0;
	return (new);
}
