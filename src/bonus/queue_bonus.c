/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:02:52 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/01 19:33:11 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_node	*pop(t_p_queue *heap)
{
	t_node	*ret;

	if (heap->size == 0)
		return (NULL);
	ret = heap->arr[heap->size];
	heap->size--;
	return (ret);
}

void	push(t_p_queue *heap, t_node *node)
{
	if (heap->size == heap->max_size)
	{
		heap->max_size *= 2;
		heap->arr = (t_node **)realloc(heap->arr, sizeof(t_node *) * (heap->max_size + 1));
	}
	heap->arr[heap->size] = node;
	heap->size++;
}

t_node	*dup_node(t_node *node)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->position.x = node->position.x;
	new_node->position.y = node->position.y;
	new_node->f_cost = node->f_cost;
	new_node->next = node->next;
	return (new_node);
}
