/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:33:21 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/13 14:02:46 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	queue_push(t_queue *queue, t_node *tmp)
{
	queue->arr[queue->end] = tmp;
	queue->end += 1;
}

t_node	*queue_pop(t_queue *queue)
{
	if (queue->start < queue->end)
	{
		queue->start += 1;
		return (queue->arr[queue->start - 1]);
	}
	else
		return (NULL);
}

void	queue_delete(t_queue *queue)
{
	while (queue->start < queue->end)
	{
		free(queue->arr[queue->start++]);
	}
}

t_node	*init_queue_node(int x, int y, int direction)
{
	t_node	*tmp;

	tmp = (t_node *)malloc(sizeof(t_node));
	tmp->position.x = x;
	tmp->position.y = y;
	tmp->direction = direction;
	return (tmp);
}
