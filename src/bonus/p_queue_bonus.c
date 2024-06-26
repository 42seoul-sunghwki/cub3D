/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:47:22 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 19:17:00 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	node_swap(t_node **arr, int i, int j)
{
	t_node	*tmp;

	tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void	max_heapify(t_p_queue *heap, int i)
{
	int		largest;
	int		left;
	int		right;
	t_node	**arr;

	arr = heap->arr;
	largest = i;
	left = 2 * i;
	right = 2 * i + 1;
	if (heap->size >= left && arr[left]->f_cost > arr[i]->f_cost)
		largest = left;
	if (heap->size >= right && arr[right]->f_cost > arr[largest]->f_cost)
		largest = right;
	if (largest != i)
	{
		node_swap(arr, i, largest);
		max_heapify(heap, largest);
	}
}

t_node	*dequeue(t_p_queue *heap)
{
	t_node	*ret;

	if (heap->size == 0)
		return (NULL);
	ret = heap->arr[1];
	heap->arr[1] = heap->arr[heap->size];
	heap->size -= 1;
	max_heapify(heap, 1);
	return (ret);
}

void	increase_value(t_p_queue *heap, int i, t_node *node)
{
	t_node	**arr;

	arr = heap->arr;
	if (node->f_cost < arr[i]->f_cost)
		return ;
	arr[i] = node;
	while (i > 1 && arr[i / 2]->f_cost < arr[i]->f_cost)
	{
		node_swap(arr, i, i / 2);
		i /= 2;
	}
}

void	enqueue(t_p_queue *heap, t_node *node)
{
	int		i;

	heap->size += 1;
	if (heap->max_size <= heap->size)
	{
		heap->max_size *= 2;
		heap->arr = realloc(heap->arr, sizeof(t_node *) * heap->max_size);
	}
	i = heap->size;
	heap->arr[i] = node;
	increase_value(heap, i, node);
}
