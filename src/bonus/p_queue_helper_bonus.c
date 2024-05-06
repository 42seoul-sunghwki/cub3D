/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_helper_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:27:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 19:35:42 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_p_queue	*init_p_queue(int size)
{
	t_p_queue	*heap;

	heap = (t_p_queue *)malloc(sizeof(t_p_queue));
	heap->arr = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	memset(heap->arr, 0, sizeof(t_node) * (size + 1));
	heap->size = 0;
	return (heap);
}

float	distance(float x, float y, float dest_x, float dest_y)
{
	return (sqrt(pow(dest_x - x, 2) + pow(dest_y - y, 2)));
}

void	delete_p_queue(t_p_queue *list, int i)
{
	t_node	*deleted;

	deleted = list->arr[i];
	list->arr[i] = list->arr[list->size];
	list->size--;
	max_heapify(list, i);
	increase_value(list, i, list->arr[i]);
}

void	sanitize_p_queue(t_p_queue *queue)
{
	int		i;
	t_node	**arr;

	arr = queue->arr;
	i = 1;
	while (i <= queue->size)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	queue->size = 0;
}
